//
// Created by kabus on 14.06.2026.
//

#ifndef PROJEKT_ABOUTPAGE_H
#define PROJEKT_ABOUTPAGE_H
#include <wx/wx.h>

wxDECLARE_EVENT(ABOUT_BACK, wxCommandEvent);

class AboutPage : public wxPanel {
public:
    AboutPage(wxWindow* parent);

private:
    void OnBack(wxCommandEvent& evt);
};



#endif //PROJEKT_ABOUTPAGE_H
