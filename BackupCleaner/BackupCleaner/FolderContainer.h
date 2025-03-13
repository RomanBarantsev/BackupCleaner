#pragma once
#include <string>
#include "FolderData.h"
#include "StoreData.h"
#include "TxtBoxAndLabel.h"

namespace BackupCleaner {
    ref class MainWindow;
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    public ref class FolderContainer : public Panel {
    private:
        int elementYSize = 20;
        Button^ BtnDeleteFolder;
        Button^ BtnSelectFolder;
        TextBox^ FolderPath;
        String^ key;
        FolderData* data;
    public:
        delegate void DeleteContainerHandler(FolderContainer^ sender); 
        event DeleteContainerHandler^ OnDeleteContainer;
        delegate void ChangeContainerKeyHandler(FolderContainer^ sender);
        event ChangeContainerKeyHandler^ OnChangeContainerKeyContainer;  

    public:
        FolderContainer(System::String^ folder, FolderData& fdata) {
            data = &fdata;
            this->Size = System::Drawing::Size(500, 70);
            this->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            // Delete button
            BtnDeleteFolder = gcnew Button();
            BtnDeleteFolder->Size = System::Drawing::Size(50, 50);
            BtnDeleteFolder->Location = Point(0, 0);
            BtnDeleteFolder->Text = "Delete Folder";
            BtnDeleteFolder->Click += gcnew EventHandler(this, &FolderContainer::OnBtnDeleteDataClick);
            this->Controls->Add(BtnDeleteFolder);

            // TextBox
            FolderPath = gcnew TextBox();
            FolderPath->Size = System::Drawing::Size(150, elementYSize);
            FolderPath->Location = Point(50, 0);
            FolderPath->Text = folder;
            FolderPath->ReadOnly = true;
            this->Controls->Add(FolderPath);

            // Select Folder Button
            BtnSelectFolder = gcnew Button();
            BtnSelectFolder->Size = System::Drawing::Size(100, elementYSize);
            BtnSelectFolder->Location = Point(200, 0);
            BtnSelectFolder->Text = "Choose folder";
            BtnSelectFolder->Click += gcnew EventHandler(this, &FolderContainer::OnBtnSelectFolderClick);
            this->Controls->Add(BtnSelectFolder);

            int xStartPos = 60;
            int yStartPos = 20;
            int xMargins=20;
            System::String^ daysTooltip = "days for which files will be stored";
            //txtlabel
            TxtBoxAndLabel^ daysTxtLabel = gcnew TxtBoxAndLabel(xStartPos, yStartPos, this, daysTooltip, data.daysToStore, "days");
        }

    private:
        void OnBtnSelectFolderClick(Object^ sender, EventArgs^ e) {
            FolderBrowserDialog^ folderDialog = gcnew FolderBrowserDialog();
            if (folderDialog->ShowDialog() == DialogResult::OK) {
                FolderPath->Text = folderDialog->SelectedPath;
            }
            OnChangeContainerKeyContainer(this);
        }

        void OnBtnDeleteDataClick(Object^ sender, EventArgs^ e) {
            OnDeleteContainer(this);
        }

    public:
        System::String^ GetKey() {
            return FolderPath->Text;
        }
        System::String^ GetKeyFromBox() {
            return FolderPath->Text;
        }
    };
}
