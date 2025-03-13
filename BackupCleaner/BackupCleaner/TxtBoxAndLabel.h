#pragma once
#include <string>

namespace BackupCleaner {
ref class FolderContainer;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

    public ref class TxtBoxAndLabel : public Panel {
    private:
        static const int spacing{ 20 };
        static const int xSize{ 50 };
        static const int ySize{ 25 };
        //--------------------------------
        Label^ lbl;
        TextBox^ txtbox;
        ToolTip^ tTip;
        int& storeValue;
        FolderContainer^ parentPanel;
    public:
        TxtBoxAndLabel(int xPosition, int yPosition, Panel^ panel, System::String^ tooltip, int& txtBox, std::string label) :
            storeValue(txtBox) {
            InitializeComponent(xPosition, yPosition, panel, tooltip, txtBox, label);
        }
    private:
        void InitializeComponent(int xPos, int yPos, Panel^ panel, System::String^ tooltip, int& txtBox, std::string& label) {
            //lbl
            lbl = gcnew Label();
            lbl->Size = System::Drawing::Size(xSize, ySize);
            lbl->Location = Point(xPos, yPos);
            System::String^ sysStr = tooltip;
            lbl->Text = sysStr;

            //File Size Text
            txtbox = gcnew TextBox();
            txtbox->Size = System::Drawing::Size(xSize, ySize);
            txtbox->Location = Point(xPos, yPos + spacing);
            System::String^ str = System::Convert::ToString(txtBox);
            txtbox->Text = str;
            txtbox->Leave += gcnew EventHandler(this, &TxtBoxAndLabel::OnTextBoxLeave);
            //ToolTip
            tTip = gcnew ToolTip();
            str = tooltip;
            tTip->SetToolTip(lbl, str);
            panel->Controls->Add(txtbox);
            panel->Controls->Add(lbl);
        }
        void OnTextBoxLeave(Object^ sender, EventArgs^ e) {
            TextBox^ tb = safe_cast<TextBox^>(sender);
            int newValue;
            if (Int32::TryParse(txtbox->Text, newValue)) {
                storeValue = newValue;  // ���������� ��������
                MessageBox::Show("����� ��������: " + storeValue);
            }
            else {
                MessageBox::Show("������! ������� �����.");
                txtbox->Text = storeValue.ToString();  // ��������������� ������ ��������
            }
        }
    };
};