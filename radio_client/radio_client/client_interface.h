#pragma once

#include <conio.h>
#include <winsock2.h> 
#include "bass.h"
#include "client.h"
#include <msclr\marshal_cppstd.h>

#include "windows.h"
#include "WinDef.h"
#include "wincrypt.h"
#include <iostream>

#pragma comment(lib, "bass.lib")

static HSTREAM stream;

namespace radio_client {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for client_interface
	/// </summary>
	public ref class client_interface : public System::Windows::Forms::Form
	{
	public:
		client_interface(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~client_interface()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected:
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::IContainer^  components;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(client_interface::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(50, 40);
			this->button1->Margin = System::Windows::Forms::Padding(2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(83, 29);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Play/Stop";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &client_interface::button1_Click);
			this->button1->StyleChanged += gcnew System::EventHandler(this, &client_interface::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(153, 40);
			this->button2->Margin = System::Windows::Forms::Padding(2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(87, 29);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Next";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &client_interface::button2_Click);
			// 
			// client_interface
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(289, 121);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"client_interface";
			this->Text = L"Music Online";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		ClientSocket sock(TCP);
		sock.Connect();
		sock.Send("give me some music");
		
		//Initializing CSP
		HCRYPTPROV hProv;
		CryptAcquireContext(&hProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, 0);
		
		//key generation
		HCRYPTHASH hHash = NULL;
		char* password_sample = "12345";
		if (!CryptCreateHash(hProv, CALG_SHA, 0, 0, &hHash))
			cout << "Error: create hash" << endl;
		if (!CryptHashData(hHash, (BYTE*)password_sample, (DWORD)strlen(password_sample), 0))
			cout << "Error: password hash" << endl;
		HCRYPTKEY hKey;
		if (!CryptDeriveKey(hProv, CALG_RC4, hHash, CRYPT_EXPORTABLE, &hKey))
			cout << "Error: key create" << endl;
		//end of key generation

		stream = BASS_StreamCreate(44100, 2, 0, STREAMPROC_PUSH, NULL);
		if (!stream)
		{
			MessageBox::Show("BASS_StreamCreate() is failed.", "Error", MessageBoxButtons::OK);
			exit(EXIT_FAILURE);
		}

		BASS_ChannelPlay(stream, FALSE);
		while (BASS_ChannelIsActive(stream) == BASS_ACTIVE_STALLED || BASS_ChannelIsActive(stream) == BASS_ACTIVE_PLAYING)
		{
			string buffer = sock.Recieve();
			char *cstr = new char[buffer.length()];
			for (int i = 0; i < buffer.length(); ++i) {
				cstr[i] = buffer[i];
			}

			DWORD tmp = buffer.length();
			if (!CryptDecrypt(hKey, 0, tmp <= buffer.length(), 0, (BYTE *)cstr, &tmp))
				cout << "ErrorDecrypt" << endl;

			BASS_StreamPutData(stream, (void *)cstr, (DWORD)buffer.length());

			delete[] cstr;
		}

		//Closing CSP
		CryptDestroyKey(hKey);
		if (hHash) CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);
	}
	
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		BASS_ChannelStop(stream);
		BASS_StreamFree(stream);
	}
};
}
