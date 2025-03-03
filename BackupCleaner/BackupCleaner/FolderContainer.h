#pragma once
#include <string>

namespace DynamicWinForms {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    public ref class FolderContainer : public Panel {
    private:
        Button^ BtnSelectFolder;
        TextBox^ FolderPath;        
        int elementYSize=20;
        int xStartPos = 160;
        int yStartPos = 0;
        // creating same txt with label(with Tooltip) for maxFile, count of backup files, etc 
        void TxtBoxAndLabel(const std::string& label, const std::string& toolTipTxt, int& value) {
            //positioning
            const int spacing = 5;
            static const int xSize = 50;
            static const int ySize = elementYSize;
            static const int xTextSpacing = spacing+xSize;
            static const int yTextSpacing = spacing+ySize;

            Label^ lbl;
            TextBox^ txtbox;
            ToolTip^ tTip;
            //lbl
            lbl = gcnew Label();
            lbl->Size = System::Drawing::Size(xSize, ySize);
            lbl->Location = Point(xStartPos, yStartPos);
            System::String^ sysStr = gcnew System::String(toolTipTxt.c_str());
            lbl->Text = sysStr;

            //File Size Text
            txtbox = gcnew TextBox();
            txtbox->Size = System::Drawing::Size(xSize, ySize);
            txtbox->Location = Point(xStartPos, yStartPos+yTextSpacing);
            txtbox->Text = "text";
            //ToolTip
            tTip = gcnew ToolTip();
            tTip->SetToolTip(lbl, "tooltip");
            this->Controls->Add(txtbox);
            this->Controls->Add(lbl);
            xStartPos += xTextSpacing;
        }

    public:
        FolderContainer(int yPos) {
            this->Size = System::Drawing::Size(500, 70);
            this->Location = Point(50, yPos);
            this->AutoScroll = true;

            //txtBox
            FolderPath = gcnew TextBox();
            FolderPath->Size = System::Drawing::Size(150, elementYSize);
            FolderPath->Location = Point(0, 0);
            FolderPath->Text = "";
            FolderPath->ReadOnly = true;

            //btn
            BtnSelectFolder = gcnew Button();
            BtnSelectFolder->Size = System::Drawing::Size(150, elementYSize);
            BtnSelectFolder->Location = Point(0, 25);
            BtnSelectFolder->Text = "Choose folder";
            //btn handler
            BtnSelectFolder->Click += gcnew EventHandler(this, &FolderContainer::OnBtnSelectFolderClick);            
            
            std::string test = "test";
            int val = 1;
            TxtBoxAndLabel(test,test, val);
            TxtBoxAndLabel(test,test, val);

            //controls to panel
            this->Controls->Add(FolderPath);
            this->Controls->Add(BtnSelectFolder);
        }
    private:
        void OnBtnSelectFolderClick(Object^ sender, EventArgs^ e) {
            FolderBrowserDialog^ folderDialog = gcnew FolderBrowserDialog();
            if (folderDialog->ShowDialog() == DialogResult::OK) {
                FolderPath->Text = folderDialog->SelectedPath; // Отображаем путь в текстбоксе
            }
        }
    };
}