#include "HudDisplay.h"

HudDisplay::HudDisplay(wxWindow *parent, wxString label, wxString initialValue) : wxPanel(parent) {
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(sizer);

    wxFont hudFont(wxSize(8, 16), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "PxPlus ToshibaSat 8x16");

    this->label = new wxStaticText(this, wxID_ANY, label);
    this->label->SetFont(hudFont);
    sizer->Add(this->label, 0, wxALIGN_CENTER | wxTOP, 4);

    value = new wxStaticText(this, wxID_ANY, initialValue);
    value->SetFont(hudFont.Scale(2.0));
    sizer->Add(value, 0, wxALIGN_CENTER);
}

void HudDisplay::SetValue(wxString value) {
    this->value->SetLabel(value);
}
