#include "serv.h"

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

		while (true) 
		{
			BaseSocket * feedback_socket = socket.Accept(TCP); // Creating a new socket for feedback
			socket.OnAccept(feedback_socket); // Answer on request
		}

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
