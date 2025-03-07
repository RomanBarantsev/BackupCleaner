#pragma once
#include <string>
namespace DynamicWinForms {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    public ref class TxtBoxAndLabel : public Panel {
    private:
        int xPos{ 0 }, yPos{ 0 };
        static const int spacing{ 5 };
        static const int xSize{ 50 };
        static const int ySize{ 25 };
        static const int xTextSpacing = spacing + xSize;
        static const int yTextSpacing = spacing + ySize;

    public:
        TxtBoxAndLabel(int& xPosition, int& yPosition, Panel^ panel, std::string& tooltip, int& txtBox, std::string label) :
            xPos(xPosition), yPos(yPosition) {
            InitializeComponent(panel, tooltip, txtBox, label);
            }
    private:
        void InitializeComponent(Panel^ panel, std::string& tooltip, int& txtBox, std::string& label) {
            Label^ lbl;
            TextBox^ txtbox;
            ToolTip^ tTip;
            //lbl
            lbl = gcnew Label();
            lbl->Size = System::Drawing::Size(xSize, ySize);
            lbl->Location = Point(xPos, yPos);
            System::String^ sysStr = gcnew System::String(tooltip.c_str());
            lbl->Text = sysStr;

            //File Size Text
            txtbox = gcnew TextBox();
            txtbox->Size = System::Drawing::Size(xSize, ySize);
            txtbox->Location = Point(xPos, yPos + yTextSpacing);
            txtbox->Text = "text";
            //ToolTip
            tTip = gcnew ToolTip();
            tTip->SetToolTip(lbl, "tooltip");
            panel->Controls->Add(txtbox);
            panel->Controls->Add(lbl);
            xPos += xTextSpacing;
        }
    };

}

