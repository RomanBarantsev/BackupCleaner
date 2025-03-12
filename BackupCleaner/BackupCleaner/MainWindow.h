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
		System::Collections::Generic::List<FolderContainer^>^ containers;
		Panel^ flowPanel;

	public:
		// Method to add a new container
		void AddContainer(FolderData& fd,System::String^ key) {
			FolderContainer^ container = gcnew FolderContainer(key, fd);
			containers->Add(container);
			flowPanel->Controls->Add(container);
			UpdateLayout();
		}

		// Method to remove a container
		void RemoveContainer(FolderContainer^ container) {
			if (containers->Contains(container)) {
				//------
				//System::String^ key = gcnew System::String(container->GetKey());
				//------
				containers->Remove(container);
				flowPanel->Controls->Remove(container);
				delete container;  // Calls destructor
				UpdateLayout();
			}
		}
	private:
		void UpdateLayout() {
			int yPos = 10;
			for each (FolderContainer ^ c in containers) {
				c->Location = System::Drawing::Point(10, yPos);
				yPos += c->Height + 10;
			}
		}
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			containers = gcnew System::Collections::Generic::List<FolderContainer^>();
			this->SuspendLayout();
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1200, 600);
			this->ResumeLayout(false);
			
			// Создаём FlowLayoutPanel
			flowPanel = gcnew Panel();
			flowPanel->Dock = DockStyle::Fill;
			this->Controls->Add(flowPanel);

			//----- FOLDER CONTAINER
			this->Text = "Backup Deleter";
			int yOffset = 25; // Initial Y position
			int yMargin = 75;

			StoreData Folders;
			FolderData fd(1, "days", 2, "size", 3, "count");
			Folders.addFolder("c:\\temp\\1", fd);            
			Folders.addFolder("c:\temp2", fd);            
			auto data = Folders.GetData();
			for (auto& folder : data)
			{
				System::String^ str = gcnew String(folder.first.c_str());
				AddContainer(folder.second, str);
			}
		}
#pragma endregion
};
}
