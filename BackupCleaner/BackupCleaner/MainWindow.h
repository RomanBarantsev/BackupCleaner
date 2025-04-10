#pragma once
#include "StoreData.h"
#include "FolderData.h"
#include "FolderContainer.h"

#include "resource.h"

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
		TableLayoutPanel^ tablePanel;
		Panel^ scrollPanel;
		StoreData* Folders;
		Panel^ pathPanel;
		TextBox^ folderPath;
		Button^ BtnNewFolder;
		Button^ BtnAddFolder;
		System::String^ tmpPath;
		FolderData* NewFolderData;
	public:
		void AddContainerToUI(FolderData*& fd, System::String^ key) {
			FolderContainer^ container = gcnew FolderContainer(key, fd);
			container->OnDeleteContainer += gcnew FolderContainer::DeleteContainerHandler(this, &MainWindow::RemoveContainer);
			container->OnChangeContainerKeyContainer += gcnew FolderContainer::ChangeContainerKeyHandler(this, &MainWindow::ChangeContainerKey);
			containers->Add(container);
			tablePanel->Controls->Add(container);
			UpdateLayout();
		}
		// Method to add a new container
		void AddContainerToData(FolderData*& fd,System::String^ key) {
			msclr::interop::marshal_context context;
			std::string nativeStr = context.marshal_as<std::string>(key);
			if (Folders->findByKey(nativeStr))
				return;
			else
				Folders->addFolder(nativeStr, fd);			
		}
		void ChangeContainerKey(FolderContainer^ container) {
			if (container->GetKey() != container->GetKeyFromBox()) {
				FolderData* fd = container->GetData();
				Folders->deleteFolder(StrSystemToNative(container->GetKey()));
				Folders->addFolder(StrSystemToNative(container->GetKeyFromBox()), fd);
			}

		}
		// Method to remove a container
		void RemoveContainer(FolderContainer^ container) {			
			Folders->deleteFolder(StrSystemToNative(container->GetKey()));
			//--------------
			if (containers->Contains(container)) {
				containers->Remove(container);
				tablePanel->Controls->Remove(container);
				delete container;  // Calls destructor
				UpdateLayout();
			}
		}
	private:
		std::string StrSystemToNative(System::String^ str) {
			msclr::interop::marshal_context context;
			return context.marshal_as<std::string>(str);
		}
		System::String^ StrNativeToSystem(std::string nativeStr) {
			return gcnew System::String(nativeStr.c_str());
		}
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
			this->ClientSize = System::Drawing::Size(600, 600);
			IntPtr iconHandle = IntPtr(LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1)));
			this->Icon = System::Drawing::Icon::FromHandle(iconHandle);
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
			// Panel with scrollbar
			scrollPanel = gcnew Panel();
			scrollPanel->Dock = DockStyle::Fill;
			scrollPanel->AutoScroll = true;
			scrollPanel->Location = System::Drawing::Point(0, pathPanel->Height);
			scrollPanel->Size = System::Drawing::Size(this->ClientSize.Width, this->ClientSize.Height - pathPanel->Height);
			scrollPanel->Anchor = AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right | AnchorStyles::Bottom;

			// Table inside scroll panel
			tablePanel = gcnew TableLayoutPanel();
			tablePanel->ColumnCount = 1;
			tablePanel->RowCount = 0;
			tablePanel->Dock = DockStyle::Top;
			tablePanel->AutoSize = true;
			tablePanel->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;

			scrollPanel->Controls->Add(tablePanel);
			this->Controls->Add(scrollPanel);

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
				AddContainerToUI(folder.second, str);
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
					
					FolderData* data;
					data = nullptr;
					AddContainerToData(data, tmpPath);
					AddContainerToUI(data,tmpPath);
				}
				
			}
#pragma endregion
};
}
