#pragma once

namespace DynamicWinForms {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    public ref class FolderContainer : public Panel {
    private:
        Button^ BtnSelectFolder;
        TextBox^ textBoxFolder;
        TextBox^ MaxSize;
        TextBox^ MaxDays;
        TextBox^ MaxCopies;
        CheckBox^ CheckBox;
    public:
        FolderContainer(int yPos) {
            this->Size = System::Drawing::Size(500, 50);
            this->Location = Point(50, yPos);

            //txtBox
            textBoxFolder = gcnew TextBox();
            textBoxFolder->Size = System::Drawing::Size(150, 25);
            textBoxFolder->Location = Point(0, 0);
            textBoxFolder->Text = "";
            textBoxFolder->ReadOnly = true;
            //btn
            BtnSelectFolder = gcnew Button();
            BtnSelectFolder->Size = System::Drawing::Size(150, 25);
            BtnSelectFolder->Location = Point(0, 25);
            BtnSelectFolder->Text = "Выбрать папку";

            //btn handler
            BtnSelectFolder->Click += gcnew EventHandler(this, &FolderContainer::OnBtnSelectFolderClick);

            //controls to panel
            this->Controls->Add(textBoxFolder);
            this->Controls->Add(BtnSelectFolder);
        }
    private:
        void OnBtnSelectFolderClick(Object^ sender, EventArgs^ e) {
            FolderBrowserDialog^ folderDialog = gcnew FolderBrowserDialog();
            if (folderDialog->ShowDialog() == DialogResult::OK) {
                textBoxFolder->Text = folderDialog->SelectedPath; // Отображаем путь в текстбоксе
            }
        }
    };
}