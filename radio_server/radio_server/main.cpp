#include "serv.h"

#include <iostream>
#include "windows.h"
#include "WinDef.h"
#include "wincrypt.h"

#define BUFFER_SIZE 128
using namespace std;

int main()
{
	try
	{
		WSADATA WsaData;
		// Initialization Winsock
		InitializationWSA(WsaData);
		
		// Create a listening socket
		ServerSocket socket(TCP);	
		
		// Bind the socket to the local IP address and port 8080
		socket.Bind();
		socket.Listen(20); 

		//Initializing CSP
		HCRYPTPROV hProv;
		//Подключаемся к криптопровайдеру типа PROV_RSA_FULL
		if (!CryptAcquireContext(&hProv, NULL, MS_DEF_PROV, PROV_RSA_FULL, 0)) throw 1;

		while (true) 
		{
			BaseSocket * feedback_socket = socket.Accept(TCP); // Creating a new socket for feedback
			socket.OnAccept(feedback_socket, hProv); // Answer on request
		}

		// Disable Winsock
		if (WSACleanup())
			throw string("cleaning of WSA");
		return 0;

		//Closing CSP
		CryptReleaseContext(hProv, 0);
	}
	catch (string s)
	{
		cout << "Error: " << s << endl;
		exit(EXIT_FAILURE);
	}
}
