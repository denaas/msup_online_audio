#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <winsock2.h> 

using std::string;
using std::endl;
using std::cout;
using std::ifstream;
using std::ios_base;

enum PROTO {TCP, UDP};

#pragma comment(lib, "ws2_32.lib")

const short int LISTEN_PORT = 8080;

void InitializationWSA(WSADATA & wsaData) {
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "WSAStartup() failed: " << GetLastError() << endl;
		WSACleanup();
		exit(1);
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
	void OnAccept(BaseSocket*);
};

/* class BaseSocket */
BaseSocket::BaseSocket(PROTO prot, SOCKET fd = INVALID_SOCKET, SocketAddress * ptr_addr = NULL) 
	: fd_socket(fd), base_sock_addr(ptr_addr)
{
	if (fd == INVALID_SOCKET && ptr_addr == NULL) {
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
		throw string("call socket recieve");
}

string BaseSocket::Recieve() 
{
	char buf[4096];
	int len = sizeof(buf);
	if (recv(fd_socket, buf, len, 0) == SOCKET_ERROR)
		throw string("call socket recieve");
	string res(buf);
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

void ExecMethodGet(BaseSocket *pConn, string recvmsg) 
{
	string res = "";
	pConn->Send(res);
}

void ServerSocket::OnAccept(BaseSocket* pConn)
{
	cout << "Get request!" << endl;
	shutdown(pConn->GetSockDescriptor(), 2);
	closesocket(pConn->GetSockDescriptor());
}