//
// Created by kabus on 14.06.2026.
//

#ifndef PROJEKT_HUDDISPLAY_H
#define PROJEKT_HUDDISPLAY_H
#include <wx/wx.h>

class HudDisplay : public wxPanel {
private:
    wxStaticText* label;
    wxStaticText* value;

public:
    HudDisplay(wxWindow* parent, wxString label, wxString initialValue);
    void SetValue(wxString value);
};



#endif //PROJEKT_HUDDISPLAY_H
