#include "client.h"

void InitializationWSA(WSADATA & wsaData) {
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		MessageBox::Show("WSAStartup() is failed.", "Error", MessageBoxButtons::OK);
		WSACleanup();
		exit(EXIT_FAILURE);
	}
}

SocketAddress::SocketAddress()
{
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(LISTEN_PORT);
}

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
			MessageBox::Show("Unsuspected value of PROTO", "Error", MessageBoxButtons::OK);
			exit(EXIT_FAILURE);
		};
		if (Result == INVALID_SOCKET)
		{
			MessageBox::Show("Socket create", "Error", MessageBoxButtons::OK);
			exit(EXIT_FAILURE);
		}
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
	int len = (int)str.length();
	if (send(fd_socket, str.c_str(), len, 0) == 0)
	{
		MessageBox::Show("Call socket send", "Error", MessageBoxButtons::OK);
		exit(EXIT_FAILURE);
	}
}

string BaseSocket::Recieve()
{
	char buf[BUF_LEN];
	int len = sizeof(buf);
	if (recv(fd_socket, buf, len, 0) == SOCKET_ERROR)
	{
		MessageBox::Show("Call socket recieve", "Error", MessageBoxButtons::OK);
		exit(EXIT_FAILURE);
	}
	string res(buf);
	return res;
}

ClientSocket::ClientSocket(PROTO p)
	: BaseSocket(p)
{
}

void ClientSocket::Connect()
{
	if (connect(fd_socket, (LPSOCKADDR)base_sock_addr, base_sock_addr->GetLength()) == SOCKET_ERROR)
	{
		MessageBox::Show("Ñan not reach server", "Error", MessageBoxButtons::OK);
		exit(EXIT_FAILURE);
	}
}
