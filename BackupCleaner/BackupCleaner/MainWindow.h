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
			
			// Создаём FlowLayoutPanel
			FlowLayoutPanel^ flowPanel = gcnew FlowLayoutPanel();
			flowPanel->Dock = DockStyle::Fill;
			//flowPanel->AutoScroll = true;  // Включаем прокрутку
			flowPanel->FlowDirection = FlowDirection::TopDown;  // Элементы вниз
			flowPanel->WrapContents = false;  // Не переносить элементы
			this->Controls->Add(flowPanel);

			//----- FOLDER CONTAINER
			this->Text = "Backup Deleter";
			int yOffset = 25; // Initial Y position
			int yMargin = 75;

			StoreData Folders;
			FolderData fd(1, "days", 2, "size", 3, "count");
			Folders.addFolder("c:\temp", fd);            
			auto data = Folders.GetData();
			for (const auto& folder : data)
			{
				System::String^ str = System::Convert::ToString(folder.first.c_str());
				DynamicWinForms::FolderContainer^ container = gcnew DynamicWinForms::FolderContainer(str,folder.second,yOffset + yMargin);
				flowPanel->Controls->Add(container);
			}
		}
#pragma endregion
};
}
