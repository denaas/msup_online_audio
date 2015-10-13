// radio_server.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using std::cout;
using std::endl;
using std::string;

int main()
{
	try
	{
		// Инициализация Winsock
		WSADATA WsaData;
		int err = WSAStartup(0x0101, &WsaData);
		if (err == SOCKET_ERROR)
		{
			cout << "WSAStartup() failed: " << GetLastError() << endl;
			return 1;
		}

		// вызов функции socket
		int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		// задание элементов структуры SOCKADDR_IN
		SOCKADDR_IN sin;
		sin.sin_family = AF_INET;
		sin.sin_port = htons(8888);
		sin.sin_addr.s_addr = INADDR_ANY;

		// связывание сокета с адресом
		err = bind(sock, (LPSOCKADDR)&sin, sizeof(sin));
		if (err == -1)
		{
			throw "call bind";
		}

		// прослушивание сокета
		if (listen(sock, SOCKMAXCONN) != 0)
		{
			throw "call listen";
		}

		// to be continue...

		return 0;
	}
	catch (string s)
	{
		cout << "Error: " << s << endl;
	}
}

