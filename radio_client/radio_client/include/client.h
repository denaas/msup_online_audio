#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <winsock2.h> 
#include <ws2tcpip.h>
#include <conio.h>

#include "bass.h"
#include <msclr\marshal_cppstd.h>


#include "windows.h"
#include "WinDef.h"
#include "wincrypt.h"

#pragma comment(lib, "bass.lib")
#pragma comment(lib, "ws2_32.lib")
#define BUF_LEN 1024 * 256

using namespace System::Windows::Forms;
using std::string;
using std::endl;
using std::cout;
using std::ifstream;
using std::ios_base;

enum PROTO {TCP, UDP};

const short int LISTEN_PORT = 8080;

void InitializationWSA(WSADATA &);

class SocketAddress
{
public:
	SocketAddress();
	int GetLength() { return sizeof(sin); }
	operator LPSOCKADDR () { (LPSOCKADDR)& sin; }
private:
	SOCKADDR_IN sin;
};



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

class ClientSocket : public BaseSocket
{
public:
	ClientSocket(PROTO);
	void Connect();
};
