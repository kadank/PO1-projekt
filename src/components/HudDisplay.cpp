//
// Created by kabus on 14.06.2026.
//

#include "HudDisplay.h"

HudDisplay::HudDisplay(wxWindow *parent, wxString label, wxString initialValue) : wxPanel(parent) {
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(sizer);

    this->label = new wxStaticText(this, wxID_ANY, label);
    sizer->Add(this->label, 0, wxALIGN_CENTER);

    value = new wxStaticText(this, wxID_ANY, initialValue);
    value->SetFont(GetFont().Scale(2.0));
    sizer->Add(value, 0, wxALIGN_CENTER);
}

void HudDisplay::SetValue(wxString value) {
    this->value->SetLabel(value);
}
