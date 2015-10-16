#include "client_app.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^ argv) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	radio_client::client_app form;
	Application::Run(%form);
	return 0;
}

