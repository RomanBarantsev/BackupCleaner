#pragma once
#include "StoreData.h"
#include "FolderData.h"
#include "FolderContainer.h"

#include <msclr\marshal_cppstd.h>
#include <msclr/marshal.h>

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
			delete Folders;
		}
	protected:

	private: System::ComponentModel::IContainer^ components;

	private:
		System::Collections::Generic::List<FolderContainer^>^ containers;
		Panel^ flowPanel;
		StoreData* Folders;
		Panel^ pathPanel;
		TextBox^ folderPath;
		Button^ BtnNewFolder;
		Button^ BtnAddFolder;
		System::String^ tmpPath;
	public:
		
		// Method to add a new container
		void AddContainer(FolderData& fd,System::String^ key) {
			msclr::interop::marshal_context context;
			std::string nativeStr = context.marshal_as<std::string>(key);
			if (Folders->findByKey(nativeStr))
				return;
			else
				Folders->addFolder(nativeStr, fd);
			//---------------
			FolderContainer^ container = gcnew FolderContainer(key, fd);
			container->OnDeleteContainer += gcnew FolderContainer::DeleteContainerHandler(this, &MainWindow::RemoveContainer);
			container->OnChangeContainerKeyContainer += gcnew FolderContainer::ChangeContainerKeyHandler(this, &MainWindow::ChangeContainerKey);
			containers->Add(container);
			flowPanel->Controls->Add(container);
			UpdateLayout();
		}
		void ChangeContainerKey(FolderContainer^ container) {
			if (container->GetKey() != container->GetKeyFromBox()) {
				//container.getData
			}

		}
		// Method to remove a container
		void RemoveContainer(FolderContainer^ container) {
			auto sysStr = container->GetKey();
			msclr::interop::marshal_context context;
			std::string nativeStr = context.marshal_as<std::string>(sysStr);
			Folders->deleteFolder(nativeStr);
			//--------------
			if (containers->Contains(container)) {
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
			// NEW FOLDER PANEL
			{
				// --- New btnPanel 
				pathPanel = gcnew Panel();
				pathPanel->Size = System::Drawing::Size(500, 70);
				pathPanel->Dock = DockStyle::Top;
				this->Controls->Add(pathPanel);
				//-----  folderPath txt box
				folderPath = gcnew TextBox();
				folderPath->Size = System::Drawing::Size(150, 50);
				folderPath->Location = Point(0, 0);
				folderPath->Text = "";
				folderPath->ReadOnly = true;
				pathPanel->Controls->Add(folderPath);
				// --- Open folder dialog button
				BtnNewFolder = gcnew Button();
				BtnNewFolder->Size = System::Drawing::Size(100, 20);
				BtnNewFolder->Location = Point(160, 0);
				BtnNewFolder->Text = "New Folder";
				BtnNewFolder->Click += gcnew EventHandler(this, &MainWindow::OnBtnNewDataClick);
				pathPanel->Controls->Add(BtnNewFolder);
				// --- Add folder button
				BtnAddFolder = gcnew Button();
				BtnAddFolder->Size = System::Drawing::Size(50, 20);
				BtnAddFolder->Location = Point(270, 0);
				BtnAddFolder->Text = "Add";
				BtnAddFolder->Click += gcnew EventHandler(this, &MainWindow::OnBtnAddClick);
				pathPanel->Controls->Add(BtnAddFolder);
			}
			// --- Add FlowLayoutPanel
			flowPanel = gcnew Panel();
			flowPanel->Size = System::Drawing::Size(1200, this->ClientSize.Height - pathPanel->Height);  // ✅ Adjust height dynamically
			flowPanel->Location = System::Drawing::Point(0, pathPanel->Height);  // ✅ Place below pathPanel
			flowPanel->Anchor = AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right | AnchorStyles::Bottom;  // ✅ Adjust on resize			
			this->Controls->Add(flowPanel);

			//----- FOLDER CONTAINER
			this->Text = "Backup Deleter";
			int yOffset = 25; // Initial Y position
			int yMargin = 75;
			//---------------
			Folders = new StoreData;
			auto data = Folders->GetData();
			for (auto& folder : data)
			{
				System::String^ str = gcnew String(folder.first.c_str());
				AddContainer(folder.second, str);
			}
		}
		private:
			void OnBtnNewDataClick(Object^ sender, EventArgs^ e) {
				FolderBrowserDialog^ folderDialog = gcnew FolderBrowserDialog();
				if (folderDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
					folderPath->Text = folderDialog->SelectedPath;
					tmpPath = folderDialog->SelectedPath;
				}				
			}
			void OnBtnAddClick(Object^ sender, EventArgs^ e) {
				FolderBrowserDialog^ folderDialog = gcnew FolderBrowserDialog();
				if (tmpPath!="") {
					std::shared_ptr<FolderData> fd = std::make_shared<FolderData>(0, 0, 0);
					AddContainer(*fd,tmpPath);
				}
				
			}
#pragma endregion
};
}
