#pragma once
#include <string>
#include "FolderData.h"
#include "StoreData.h"
#include "TxtBoxAndLabel.h"
#include "MainWindow.h"

namespace DynamicWinForms {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    public ref class FolderContainer : public Panel {
    private: 
        int elementYSize=20;
        int xStartPos = 160;
        int yStartPos = 0;
        Button^ BtnDeleteFolder;
        Button^ BtnSelectFolder;
        TextBox^ FolderPath; 

    public:
        FolderContainer(System::String^ folder,FolderData data,int yPos) {
            this->Size = System::Drawing::Size(500, 70);
            this->Location = Point(50, yPos);
            this->AutoScroll = true;            
            this->BackColor = Color::LightGray;            

            //delete button
            BtnDeleteFolder = gcnew Button();
            BtnDeleteFolder->Size = System::Drawing::Size(50, 50);
            BtnDeleteFolder->Location = Point(0, 0);
            BtnDeleteFolder->Text = "Delete Folder";
            //btn handler
            BtnDeleteFolder->Click += gcnew EventHandler(this, &FolderContainer::OnBtnDeleteDataClick);
            this->Controls->Add(BtnDeleteFolder);

            //txtBox
            FolderPath = gcnew TextBox();
            FolderPath->Size = System::Drawing::Size(150, elementYSize);
            FolderPath->Location = Point(50, 0);
            FolderPath->Text = "";
            FolderPath->ReadOnly = true;
            this->Controls->Add(FolderPath);                 

            //btn
            BtnSelectFolder = gcnew Button();
            BtnSelectFolder->Size = System::Drawing::Size(100, elementYSize);
            BtnSelectFolder->Location = Point(200,0);
            BtnSelectFolder->Text = "Choose folder";
            BtnSelectFolder->Click += gcnew EventHandler(this, &FolderContainer::OnBtnSelectFolderClick);
            this->Controls->Add(BtnSelectFolder);

            int xStartPos = 50;
            int yStartPos = 25;
            int xMargin = 75;
            TxtBoxAndLabel^ Counttxtlabel = gcnew TxtBoxAndLabel(xStartPos, yStartPos,this,data.countFilesTooltip,data.countFiles,"File count");
            TxtBoxAndLabel^ Daystxtlabel = gcnew TxtBoxAndLabel(xStartPos+xMargin, yStartPos,this,data.daysToStoreTooltip,data.daysToStore,"Days to store");
        }
    private:
        void OnBtnSelectFolderClick(Object^ sender, EventArgs^ e) {
            FolderBrowserDialog^ folderDialog = gcnew FolderBrowserDialog();
            if (folderDialog->ShowDialog() == DialogResult::OK) {
                FolderPath->Text = folderDialog->SelectedPath; // Отображаем путь в текстбоксе
            }
        }
        void OnBtnDeleteDataClick(Object^ sender, EventArgs^ e) {
            
        }
    };
}