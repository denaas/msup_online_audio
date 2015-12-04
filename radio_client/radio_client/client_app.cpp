#include "client_app.h"

#include <iostream>
#include "windows.h"
#include "WinDef.h"
#include "wincrypt.h"


#define BUFFER_SIZE 128
using namespace std;

using namespace System;
using namespace System::Windows::Forms;

[STAThread]	
//int main(array<String^>^ argv)
int main()
{
	WSADATA WsaData;
	InitializationWSA(WsaData);
	
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	radio_client::client_app form;
	Application::Run(%form);

	if (WSACleanup())
	{
		MessageBox::Show("WSACleanup() is failed.", "Error", MessageBoxButtons::OK);
		exit(EXIT_FAILURE);
	}
	return 0;
}

