/* Release x86

Check correct directory of include and lib files!!!
Project / Properties / C/C++ / General / Additional... / path to include
Project / Properties / Linker / General / Additional Library Directories / path to lib

If there is a problem with CryptoAPI:
Project / Properties / Linker / Input / Additional Dependencies / advapi32.lib.
*/

#include "client_app.h"
#include "windows.h"
#include "WinDef.h"
#include "wincrypt.h"

#define BUFFER_SIZE 128

using namespace System;
using namespace System::Windows::Forms;

[STAThread]	
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



