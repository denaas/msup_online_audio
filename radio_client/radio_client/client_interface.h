#pragma once

#include <conio.h>
#include <winsock2.h> 
#include "bass.h"
#include "client.h"
#include <msclr\marshal_cppstd.h>


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


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(28, 54);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(124, 45);
			this->button1->TabIndex = 0;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &client_interface::button1_Click);
			this->button1->StyleChanged += gcnew System::EventHandler(this, &client_interface::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(218, 54);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(130, 45);
			this->button2->TabIndex = 1;
			this->button2->Text = L"button2";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &client_interface::button2_Click);
			// 
			// client_interface
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(386, 178);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"client_interface";
			this->Text = L"client_interface";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		/*
		char filename[] = "1.mp3";

		stream = BASS_StreamCreateFile(FALSE, filename, 0, 0, 0);

		if (!stream) 
		{
			MessageBox::Show("BASS_StreamCreateFile() is failed.", "Error", MessageBoxButtons::OK);
			exit(-1);
		}

		BASS_ChannelPlay(stream, FALSE);

		while (BASS_ChannelIsActive(stream) != BASS_ACTIVE_STOPPED)
		{
			Sleep(200);
		}
		*/

		//char url[] = "http://127.0.0.1:8080";

		/* Create stream, binding with url */
		/*stream = BASS_StreamCreateURL(url, 0, 0, NULL, 0);
		if (!stream) 
		{
			MessageBox::Show("BASS_StreamCreateURL() is failed.", "Error", MessageBoxButtons::OK);
			exit(EXIT_FAILURE);
		}*/

		/* Play sound */
		/*BASS_ChannelPlay(stream, FALSE);

		while (!kbhit()) Sleep(200);

		BASS_ChannelStop(stream);

		BASS_StreamFree(stream);
		*/
		
		
	}
	
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		//BASS_ChannelStop(stream);
		//BASS_StreamFree(stream);
	}
};
}
