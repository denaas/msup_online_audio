#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <winsock2.h> 
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

using namespace System::Windows::Forms;

#define BUF_LEN 1024 * 256

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
