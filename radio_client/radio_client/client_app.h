#pragma once
#include "client_interface.h"

void CreateStream();

// *******************************************************************
// *******************************************************************

using namespace System::Windows::Forms;

namespace radio_client {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// ������ ��� client_app
	/// </summary>
	public ref class client_app : public System::Windows::Forms::Form
	{
	public:
		client_app(void)
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~client_app()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  textBox1;
	protected:
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;


	protected:

	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(client_app::typeid));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(16, 32);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(306, 26);
			this->textBox1->TabIndex = 0;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(16, 105);
			this->textBox2->Name = L"textBox2";
			this->textBox2->PasswordChar = '*';
			this->textBox2->Size = System::Drawing::Size(306, 26);
			this->textBox2->TabIndex = 1;
			this->textBox2->Text = L"password";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(48, 20);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Login";
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 82);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(78, 20);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Password";
			// 
			// button1
			// 
			this->button1->AutoSize = true;
			this->button1->Location = System::Drawing::Point(16, 149);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(150, 40);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Sign in";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &client_app::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(172, 149);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(150, 40);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Sign up";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// client_app
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(339, 208);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"client_app";
			this->Text = L"Online radio";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		HCRYPTKEY KeyGeneration1(ClientSocket *sock, HCRYPTPROV hProv) {
			//NEW KEY GENERATION

			//1st
			HCRYPTKEY hEphKey;
			CryptGenKey(hProv, CALG_RSA_KEYX, CRYPT_EXPORTABLE, &hEphKey);
			DWORD keylen;
			CryptExportKey(hEphKey, NULL, PUBLICKEYBLOB, 0, NULL, &keylen);
			LPBYTE KeyBlob;
			KeyBlob = (BYTE *)malloc(keylen);
			CryptExportKey(hEphKey, NULL, PUBLICKEYBLOB, 0, KeyBlob, &keylen);
			//KeyBlob -> trans
			string trans = "";
			for (int i = 0; i < keylen; i++) {
				trans += KeyBlob[i];
			}
			sock->Send(trans);

			//2nd
			HCRYPTKEY SecKey;
			trans = "";
			trans = sock->Recieve();

			DWORD dwBlobLen = trans.length(); //����� ����������� SecKeyBlob
			BYTE *SecKeyBlob = (BYTE *)malloc(dwBlobLen);
			// trans -> SecKeyBlob
			for (int i = 0; i < dwBlobLen; i++) {
				SecKeyBlob[i] = trans[i];
			}
			// SecKeyBlob -> SecKey
			CryptImportKey(hProv, SecKeyBlob, dwBlobLen, hEphKey, 0, &SecKey);


			//3
			//Destroy hEphKey

			return SecKey;

		}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		/*
		System::String^ managed_str1 = textBox1->Text;
		std::string unmanaged_str1 = msclr::interop::marshal_as<std::string>(managed_str1);
		System::String^ managed_str2 = textBox2->Text;
		std::string unmanaged_str2 = msclr::interop::marshal_as<std::string>(managed_str2);

		std::string msg = unmanaged_str1 + "/" + unmanaged_str2;
		sock.Send(msg);

		string recv_msg = sock.Recieve();
		String ^ recv_msg_sys = gcnew String(recv_msg.c_str());
		*/

		// if authorization has been successful, then ...

		ClientSocket sock(TCP);
		sock.Connect();
		sock.Send("SYN");

		// **************************************************************
		CreateStream();


		//Initializing CSP
		HCRYPTPROV hProv;
		CryptAcquireContext(&hProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, 0);

		//key generation
		HCRYPTHASH hHash = NULL;
		char* password_sample = "12345";
		if (!CryptCreateHash(hProv, CALG_SHA, 0, 0, &hHash))
			cout << "Error: create hash" << endl;
		if (!CryptHashData(hHash, (BYTE *) password_sample, (DWORD) strlen(password_sample), 0))
			cout << "Error: password hash" << endl;
		HCRYPTKEY hKey;
		if (!CryptDeriveKey(hProv, CALG_RC4, hHash, CRYPT_EXPORTABLE, &hKey))
			cout << "Error: key create" << endl;
		//end of key generation
		string buffer = "";
		while ((buffer = sock.Recieve()) != "eof")
		{
			char * cstr = new char[buffer.length()];
			for (int i = 0; i < buffer.length(); ++i)
				cstr[i] = buffer[i];

			DWORD tmp = buffer.length();

			if (!CryptDecrypt(hKey, 0, tmp <= buffer.length(), 0, (BYTE *)cstr, &tmp))
				cout << "ErrorDecrypt" << endl;

			if (BASS_StreamPutData(stream, (void *)cstr, (DWORD)buffer.length()) == -1)
				std::cout << "BASS_StreamPutData() is failse with " << BASS_ErrorGetCode() << std::endl;

			delete[] cstr;
		}

		//Closing CSP
		CryptDestroyKey(hKey);
		if (hHash) CryptDestroyHash(hHash);
		CryptReleaseContext(hProv, 0);

		client_interface^ form = gcnew client_interface;
		this->Hide();
		form->Show();
	}
};
}

void CreateStream()
{
	if (!BASS_Init(-1, 44100, BASS_DEVICE_3D, 0, NULL))
	{
		MessageBox::Show("BASS_Init() is failed.", "Error", MessageBoxButtons::OK);
		exit(EXIT_FAILURE);
	}

	stream = BASS_StreamCreate(44100, 2, 0, STREAMPROC_PUSH, NULL);

	if (!stream)
	{
		MessageBox::Show("BASS_StreamCreate() is failed.", "Error", MessageBoxButtons::OK);
		exit(EXIT_FAILURE);
	}
}