#include "serv.h"

using namespace std;

int main()
{
	try
	{
		WSADATA WsaData;
		// Initialization Winsock
		InitializationWSA(WsaData);
		
		// Creating sockets
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
			BaseSocket * feedback_socket = socket.Accept(TCP); 
			socket.OnAccept(feedback_socket, hProv); 
		}

		//Closing CSP
		CryptReleaseContext(hProv, 0);

		// Disable Winsock
		if (WSACleanup())
			throw string("cleaning of WSA");
		return 0;	
	}
	catch (string s)
	{
		cout << "Error: " << s << endl;
		exit(EXIT_FAILURE);
	}
}
