#pragma once

#include <Windows.h>
#include <iostream>


namespace DLLInject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	 /// <summary>
	 /// Initializing the array to the actual script we are going to use for the cheats 
	 /// Being the num_myCheat_InstrBytes, the number of bytes to re-write
	 /// Both chars are written in shell code
	 /// cheat_myCheat_istr is the actual cheat activated
	 /// original_myCheat_Instr is the state of the original instruction for turnning it off
	 /// myCheat_InstrAddress location where we are replacing the address
	 /// </summary>
	 /// Trying ammo cheat v
	// char cheat_myCheat_Instr[] = { '\xAD', '\xDE', '\xAE', '\xD4', '\x00', '\x00', '\x00', '\xA4', '\xEC' };
	// char original_myCheat_Instr[] = { "\x29\x8C\x90\xA4\x00\x00\x00" };
	// Tried this but will not work since we are just setting bytes
	/*
	char cheat_myCheat_Instr[] = { "\x89\x84\x9E\xA4\x00\x00\x00" };
	int num_myCheat_InstrBytes = sizeof(cheat_myCheat_Instr);
	char original_myCheat_Instr[] = { "\x89\x84\x9E\xA4\x00\x00\x00" };*/
	// Setting only the address to write
	DWORD myCheat_InstrAddress = 0x0050D24C;
	
	/// <summary>
	/// Summary for StatusWindow
	/// </summary>
	public ref class StatusWindow : public System::Windows::Forms::Form
	{
	public:
		StatusWindow(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~StatusWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  submitButton;
	protected: 
	private: System::Windows::Forms::TextBox^  inputTextBox;


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
			this->submitButton = (gcnew System::Windows::Forms::Button());
			this->inputTextBox = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// submitButton
			// 
			this->submitButton->Location = System::Drawing::Point(127, 59);
			this->submitButton->Name = L"submitButton";
			this->submitButton->Size = System::Drawing::Size(163, 41);
			this->submitButton->TabIndex = 0;
			this->submitButton->Text = L"Submit";
			this->submitButton->UseVisualStyleBackColor = true;
			this->submitButton->Click += gcnew System::EventHandler(this, &StatusWindow::submitButton_Click);
			// 
			// inputTextBox
			// 
			this->inputTextBox->Location = System::Drawing::Point(37, 26);
			this->inputTextBox->Name = L"inputTextBox";
			this->inputTextBox->Size = System::Drawing::Size(337, 20);
			this->inputTextBox->TabIndex = 1;
			this->inputTextBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &StatusWindow::inputTextBox_KeyDown);
			// 
			// StatusWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(401, 109);
			this->Controls->Add(this->inputTextBox);
			this->Controls->Add(this->submitButton);
			this->Name = L"StatusWindow";
			this->Text = L"CommandWindow";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void inputTextBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 if(e->KeyCode == Keys::Enter)
				 {
					 processInput();
				 }

			 }

	private: System::Void submitButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 processInput();
			 }

	private: System::Void processInput() {
				 String^ input = inputTextBox->Text;
				 
				 inputTextBox->Text = "";				 
				 
				 // Cheats activation
				 // Splitting the string to get the cheat name and the actual ammo value to set
				 String^ cheatString = input->Split(' ')[0];
				 String^ ammoToWrite = input->Split(' ')[1];

				 // Type Casting the user input to a byte value and using it to initialize our byte to write
				 char ammoAsByte[] = { Convert::ToByte(Convert::ToInt64(ammoToWrite)) };
				 
				 // Getting the size of our bytes to write
				 int ammoSize = sizeof(ammoAsByte);

				 // Checking if the cheat is right 
				 if(String::Compare(cheatString, "ammo", true) == 0)
					overwriteMemory(myCheat_InstrAddress, ammoAsByte, ammoSize);

				 //else if(String::Compare(input, "ammo cheat off", true) == 0)
					// overwriteMemory(myCheat_InstrAddress, original_myCheat_Instr, num_myCheat_InstrBytes);
			 }

	private: System::Void overwriteMemory(DWORD addressToWrite, char* valueToWrite, int numBytesToWrite) {
				 // Changes file access type by storing the previous access type
				 // and restores right after memory is written
				 unsigned long savedProtection;
				 
				 // Storing previous perms in the saved protection and Giving our address read and write perms 
				 VirtualProtect((LPVOID)(addressToWrite), numBytesToWrite, PAGE_EXECUTE_READWRITE, &savedProtection);

				 // Overwriting the previous value with this new memory into the program
				 memcpy((LPVOID)(addressToWrite), valueToWrite, numBytesToWrite);
				 
				 // Returning the permissions back to what savedProtection state had
				 VirtualProtect((LPVOID)(addressToWrite), numBytesToWrite, savedProtection, NULL);
			 }
	};


}
