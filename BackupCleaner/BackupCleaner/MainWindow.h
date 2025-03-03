#pragma once
#include "FolderContainer.h"

namespace BackupCleaner {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainWindow
	/// </summary>
	//--------------------------------------------------------------------------------------------------
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		MainWindow(void)
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
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	protected:

	private: System::ComponentModel::IContainer^ components;

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
			this->SuspendLayout();
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1200, 600);
			this->ResumeLayout(false);
			//----- FOLDER CONTAINER
			this->Text = "Backup Deleter";
			int yOffset = 25; // Initial Y position
			int yMargin = 75;

			Button^ BtnDeleteFolder;
			BtnDeleteFolder = gcnew Button();
			BtnDeleteFolder->Size = System::Drawing::Size(50, 50);
			BtnDeleteFolder->Location = Point(0, yOffset);
			BtnDeleteFolder->Text = "Delete Folder";

			DynamicWinForms::FolderContainer^ container = gcnew DynamicWinForms::FolderContainer(yOffset);
			DynamicWinForms::FolderContainer^ container2 = gcnew DynamicWinForms::FolderContainer(yOffset+ yMargin);
			this->Controls->Add(container);
			this->Controls->Add(container2);		
			this->Controls->Add(BtnDeleteFolder);
		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		
	}
};
}
