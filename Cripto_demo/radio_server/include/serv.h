#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <winsock2.h> 

#include "windows.h"
#include "WinDef.h"
#include "wincrypt.h"

#include "sha_256.h"
#include "registr.h"
#include "Criptofunction.h"
#pragma comment(lib, "ws2_32.lib")

#define BUF_LEN 1024
#define BITRATE 256
const long stream_pack_length = 1024 * BITRATE;

using std::string;
using std::endl;
using std::cout;
using std::ifstream;
using std::ios_base;

enum PROTO {TCP, UDP};

const short int LISTEN_PORT = 8080;

void InitializationWSA(WSADATA & wsaData) {
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "WSAStartup() failed: " << GetLastError() << endl;
		WSACleanup();
		exit(EXIT_FAILURE);
	}	
}

// Declaration of class Socket's Address 
class SocketAddress
{
public:
	SocketAddress();
	int GetLength() { return sizeof(sin); }
	operator LPSOCKADDR () { (LPSOCKADDR)& sin; }
private:
	SOCKADDR_IN sin;
};

// Description of class SocketAddress 
SocketAddress::SocketAddress()
{
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(LISTEN_PORT);
}


// Declaration of class BaseSocket 
class BaseSocket
{
public:
	BaseSocket(PROTO, SOCKET, SocketAddress *);
	virtual ~BaseSocket();
	SOCKET GetSockDescriptor() { return fd_socket; }
	string Recieve();
	void Send(string);
protected:
	SOCKET fd_socket;
	SocketAddress * base_sock_addr;
};

class ServerSocket : public BaseSocket
{
public:
	ServerSocket(PROTO);
	BaseSocket* Accept(PROTO);
	void Bind();
	void Listen(int);
	void OnAccept(BaseSocket *, HCRYPTPROV);
};

/* class BaseSocket */
BaseSocket::BaseSocket(PROTO prot, SOCKET fd = INVALID_SOCKET, SocketAddress * ptr_addr = NULL) 
	: fd_socket(fd), base_sock_addr(ptr_addr)
{
	if (fd == INVALID_SOCKET && ptr_addr == NULL) 
	{
		SOCKET Result;
		base_sock_addr = new SocketAddress;
		switch (prot)
		{
		case TCP:
			Result = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			break;
		case UDP:
			Result = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
			break;
		default:
			throw string("unsuspected value of PROTO");
		};
		if (Result == INVALID_SOCKET)
			throw string("socket create");
		fd_socket = Result;
	}
}

BaseSocket::~BaseSocket()
{
	shutdown(fd_socket, 2);
	closesocket(fd_socket);
	delete base_sock_addr;
}

void BaseSocket::Send(string str)
{
	int len = (int) str.length();
	if (send(fd_socket, str.c_str(), len, 0) == 0)
		throw string("Call socket send");
}

string BaseSocket::Recieve()
{
	char buf[BUF_LEN];
	string res = "";
	unsigned int len = sizeof(buf);
	unsigned int recv_len = 0; 
	if ((recv_len = recv(fd_socket, buf, len, 0)) == SOCKET_ERROR)
		throw string("call socket recieve");
	for (unsigned int i = 0; i < recv_len; ++i)
		res += buf[i];
	return res;
}

/* description of class ServerSocket */
ServerSocket::ServerSocket(PROTO p)
	: BaseSocket(p)
{
	BOOL bOptVal = TRUE;
	int bOptLen = sizeof(BOOL);
	int Result = setsockopt(fd_socket, SOL_SOCKET, SO_KEEPALIVE, (char *)&bOptVal, bOptLen);
	if (Result == SOCKET_ERROR) 
		throw string("setsockopt for SO_KEEPALIVE failed");
}

BaseSocket* ServerSocket::Accept(PROTO p)
{
	cout << "Waiting for request..." << endl;
	SocketAddress * feedback_addr = new SocketAddress;
	int feedback_addr_size = feedback_addr->GetLength();
	SOCKET fd = accept(fd_socket, (LPSOCKADDR)feedback_addr, &feedback_addr_size);
	if (fd == INVALID_SOCKET)
		throw string("call accept");
	BaseSocket * ptr_base_sock = new BaseSocket(p, fd, feedback_addr);
	return ptr_base_sock;
}

void ServerSocket::Bind()
{
	if (bind(fd_socket, (LPSOCKADDR)base_sock_addr, base_sock_addr->GetLength()) == SOCKET_ERROR)
		throw string("call bind");
}

void ServerSocket::Listen(int back_log)
{
	if (listen(fd_socket, back_log) != 0)
		throw string("call listen");
}

HCRYPTKEY KeyGeneraton(BaseSocket* pConn, HCRYPTPROV hProv) {
	//1st
	//�������� public key �������
	HCRYPTKEY hPubKey;
	string str = "";
	str = pConn->Recieve();
	//HCRYPTKEY hPubKey;
	DWORD dwBlobLen = str.length();  //����� ����������� KeyBlob
	LPBYTE KeyBlob = (BYTE *)malloc(dwBlobLen);
	//str -> KeyBlob
	for (int i = 0; i < dwBlobLen; i++) {
		KeyBlob[i] = str[i];
	}
	//KeyBlob -> hPubKey
	CryptImportKey(hProv, KeyBlob, dwBlobLen, 0, 0, &hPubKey);
	cout << "1 step over" << endl;
	//2nd 
	//���������� ���������� ����
	HCRYPTKEY hKey;
	CryptGenKey(hProv, CALG_RC4, CRYPT_EXPORTABLE, &hKey);
	CryptExportKey(hKey, hPubKey, PRIVATEKEYBLOB, 0, NULL, &dwBlobLen);
	LPBYTE SecKeyBlob = (BYTE *)malloc(dwBlobLen);
	// hKey -> KeyBlob
	CryptExportKey(hKey, hPubKey, PRIVATEKEYBLOB, 0, SecKeyBlob, &dwBlobLen);
	// KeyBlob -> str
	str = "";
	for (int i = 0; i < dwBlobLen; i++) {
		str += SecKeyBlob[i];
	}
	pConn->Send(str);
	cout << "2 step over" << endl;

	//3
	//Destroy hPubKey
	return hKey;
}


void ServerSocket::OnAccept(BaseSocket* pConn, HCRYPTPROV hProv)
{
	cout << "Get request:";
	string str = pConn->Recieve();
	cout << str << endl;

	/*
	* Creating a new secure connection
	*/
	//key generation
	HCRYPTHASH hHash = NULL;
	char* password_sample = "12345";
	if (!CryptCreateHash(hProv, CALG_SHA, 0, 0, &hHash))
		throw string("CreateHash");
	if (!CryptHashData(hHash, (BYTE*)password_sample, (DWORD)strlen(password_sample), 0))
		throw string("CryptHashData");
	HCRYPTKEY hKey;
	if (!CryptDeriveKey(hProv, CALG_RC4, hHash, CRYPT_EXPORTABLE, &hKey))
		throw string("DeriveKey");
	//end of key generation

	/*
	* Authentification procedure
	*/

	/*
	 * Sending audio
	 */
	WIN32_FIND_DATA FindFileData;
	HANDLE hfile;

	hfile = FindFirstFile(L"contents/*", &FindFileData);

	if (hfile != INVALID_HANDLE_VALUE)
	{
		do
		{
			
			wstring ws(FindFileData.cFileName);
			std::string fname(ws.begin(), ws.end());

			std::cout << fname << std::endl;

			if (strstr(fname.c_str(),".wav")) 
			{
				ifstream in_audio_file("contents/" + fname, std::ios::binary);

				if (!in_audio_file.is_open())
				{
					cout << "Error: Input Audio is not opened." << endl;
					system("pause");
					exit(-1);
				}

				string buffer;
				char ch;
				DWORD tmp = 0;

				while (!in_audio_file.eof())
				{
					buffer = "";
					for (int i = 0; i < stream_pack_length; ++i)
					{
						in_audio_file.get(ch);
						buffer += ch;
					}
					char cstr1[stream_pack_length];
					char* cstr;
					cstr = cstr1;
					for (int i = 0; i < stream_pack_length; ++i) {
						cstr[i] = buffer[i];
					}

					tmp = stream_pack_length;
					//if (!CryptEncrypt(hKey, 0, tmp <= stream_pack_length, 0, (BYTE *)cstr, &tmp, stream_pack_length))
						//throw string("ErrorEncrypt");
					unsigned char kSeltTestGost14OfbSV[32] =
					{
					0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xce, 0xf0, 0xa1, 0xb2, 0xc3, 0xd4, 0xe5, 0xf0, 0x01, 0x12,
					0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x90, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19
					};
					const size_t svLen = sizeof(kSeltTestGost14OfbSV) / sizeof(kSeltTestGost14OfbSV[0]);
					unsigned char outText[stream_pack_length];
					unsigned char ctx[kOfb14ContextLen];
					using namespace Cripto;
					Criptofunction x;
					unsigned char kSeltTestGost14MasterKeyData[32] =
					{
					0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66,0x77,
					0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10, 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef
					};
					if (x.init_ofb_14(kSeltTestGost14MasterKeyData, ctx, kBlockLen14, kSeltTestGost14OfbSV, svLen, 0, 0))
					throw string("ErrorEncrypt");

					if (x.encrypt_ofb(ctx,(unsigned char*) cstr, outText, stream_pack_length))
					throw string("ErrorEncrypt");
					cstr = (char*)outText;
					x.free_ofb(ctx);

					string resstr = "";
					for (int i = 0; i < stream_pack_length; ++i) {
						resstr += cstr[i];
					}

					pConn->Send(resstr);
				}
			}
		} while (FindNextFile(hfile, &FindFileData) != 0);

		pConn->Send("eof");
		FindClose(hfile);
	}


	
	CryptDestroyKey(hKey);
	if (hHash) CryptDestroyHash(hHash);
}