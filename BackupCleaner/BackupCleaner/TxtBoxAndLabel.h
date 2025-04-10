#pragma once
#include <string>
#include "MainWindow.h"

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
        static const int spacing{ 50 };
        static const int TXTxSize{ 50 };
        static const int TXTySize{ 25 }; 
        static const int LBLxSize{ 200 };
        static const int LBLySize{ 25 };
        //--------------------------------
        Label^ lbl;
        TextBox^ txtbox;
        ToolTip^ tTip;
        int& storeValue;
        Panel^ parentPanel;
    public:
        TxtBoxAndLabel(int xPosition, int yPosition, Panel^ parent, System::String^ tooltip, int& value, std::string label) :
            storeValue(value) {
            InitializeComponent(xPosition, yPosition, parent, tooltip, value, label);
        }
    private:
        void InitializeComponent(int xPos, int yPos, Panel^ panel, System::String^ tooltip, int& txtBox, std::string& label) {
            //lbl
            lbl = gcnew Label();
            lbl->Size = System::Drawing::Size(LBLxSize, LBLySize);
            lbl->Location = Point(xPos, yPos);
            System::String^ sysStr = tooltip;
            lbl->Text = sysStr;

            //File Size Text
            txtbox = gcnew TextBox();
            txtbox->Size = System::Drawing::Size(TXTxSize, TXTySize);
            txtbox->Location = Point(xPos+LBLxSize, yPos);
            System::String^ str = System::Convert::ToString(txtBox);
            txtbox->Text = str;
            txtbox->Leave += gcnew EventHandler(this, &TxtBoxAndLabel::OnTextBoxLeave);
            txtbox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &TxtBoxAndLabel::OnKeyDown);
            //ToolTip
            tTip = gcnew ToolTip();
            str = tooltip;
            tTip->SetToolTip(lbl, str);
            parentPanel = panel;
            panel->Controls->Add(txtbox);
            panel->Controls->Add(lbl);
        }
        void OnTextBoxLeave(Object^ sender, EventArgs^ e) {
            SetValue();
        }
        void SetValue() {
            int newValue;
            if (Int32::TryParse(txtbox->Text, newValue)) {
                storeValue = newValue;
            }
            else {
                txtbox->Text = newValue.ToString();
            }
        }
        void OnKeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
        {
            if (e->KeyCode == Keys::Enter) {
                e->SuppressKeyPress = true;
                SetValue();
                txtbox->Enabled = false;
                txtbox->Enabled = true;
            }
			
        }
        
    };
};

