#pragma once
#include "client.h"

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
	private: System::Windows::Forms::TrackBar^  trackBar1;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(client_interface::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(124, 45);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Play";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &client_interface::button1_Click);
			this->button1->StyleChanged += gcnew System::EventHandler(this, &client_interface::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(142, 12);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(130, 45);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Sign Out";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &client_interface::button2_Click);
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(288, 12);
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(143, 69);
			this->trackBar1->TabIndex = 2;
			this->trackBar1->Value = 5;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &client_interface::trackBar1_Scroll);
			// 
			// client_interface
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(455, 81);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"client_interface";
			this->Text = L"Music Online";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	static bool flag = false;
	static QWORD pos = 0;
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
	{		
		if (!flag)
		{
			flag = true;
			this->button1->Text = L"Pause";
			pos = BASS_StreamGetFilePosition(stream, BASS_FILEPOS_BUFFER);
			BASS_ChannelSetPosition(stream, pos, BASS_POS_BYTE);
			BASS_ChannelPlay(stream, FALSE);
		}
		else
		{
			flag = false;
			this->button1->Text = L"Play";
			BASS_ChannelPause(stream);
		}
	}
	
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		BASS_Free();
		exit(EXIT_SUCCESS);
	}
private: System::Void trackBar1_Scroll(System::Object^  sender, System::EventArgs^  e) {
	BASS_SetVolume((float) (this->trackBar1->Value) / this->trackBar1->Maximum);
}
};
}
