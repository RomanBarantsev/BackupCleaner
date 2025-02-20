#pragma once

namespace DynamicWinForms {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    public ref class FolderContainer : public Panel {
    private:
        Button^ BtnSelectFolder;
        TextBox^ textBox;
        TextBox^ MaxSize;
        TextBox^ MaxDays;
        TextBox^ MaxCopies;
    public:
        FolderContainer(int yPos) {
            this->Size = System::Drawing::Size(250, 50);
            this->Location = Point(50, yPos);

            //txtBox
            textBox = gcnew TextBox();
            textBox->Size = System::Drawing::Size(150, 25);
            textBox->Location = Point(5, 10);
            textBox->Text = "textBox";

            //btn
            BtnSelectFolder = gcnew Button();
            BtnSelectFolder->Size = System::Drawing::Size(150, 25);
            BtnSelectFolder->Location = Point(130, 10);
            BtnSelectFolder->Text = "Folder";

            //btn handler
            BtnSelectFolder->Click += gcnew EventHandler(this, &FolderContainer::OnBtnSelectFolderClick);

            //controls to panel
            this->Controls->Add(textBox);
            this->Controls->Add(BtnSelectFolder);
        }
    private:
        void OnBtnSelectFolderClick(Object^ sender, EventArgs^ e) {
            MessageBox::Show("clicked");
        }
    };
}