//
// Created by kabus on 14.06.2026.
//

#include "AboutPage.h"

wxDEFINE_EVENT(ABOUT_BACK, wxCommandEvent);

AboutPage::AboutPage(wxWindow *parent) : wxPanel(parent) {
    wxBoxSizer *aboutOuterSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *aboutSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText *about = new wxStaticText(this, wxID_ANY, "O autorach");
    about->SetFont(GetFont().Scale(3.0));
    aboutSizer->Add(about, 0, wxALIGN_CENTER | wxBOTTOM, 10);

    aboutOuterSizer->AddStretchSpacer(1);
    aboutOuterSizer->Add(aboutSizer, 0, wxALIGN_CENTER);
    aboutOuterSizer->AddStretchSpacer(1);
    SetSizer(aboutOuterSizer);

    wxGridSizer *aboutContentSizer = new wxGridSizer (2,2,20,20);
    aboutSizer->Add(aboutContentSizer, 0, wxALIGN_CENTER);


    wxBoxSizer *Driansizer = new wxBoxSizer(wxVERTICAL);
    Driansizer -> SetMinSize(160,100);
    aboutContentSizer->Add(Driansizer, 0, wxALIGN_CENTER);

    wxBoxSizer *Kejbasizer = new wxBoxSizer(wxVERTICAL);
    Kejbasizer -> SetMinSize(160,100);
    aboutContentSizer->Add(Kejbasizer, 0, wxALIGN_CENTER);

    wxBoxSizer *Igorsizer = new wxBoxSizer(wxVERTICAL);
    Igorsizer -> SetMinSize(160,100);
    aboutContentSizer->Add(Igorsizer, 0, wxALIGN_CENTER);

    wxBoxSizer *Kykolsizer = new wxBoxSizer(wxVERTICAL);
    Kykolsizer -> SetMinSize(160,100);
    aboutContentSizer->Add(Kykolsizer, 0, wxALIGN_CENTER);

    wxStaticText *Drian = new wxStaticText(this, wxID_ANY, "Drian");
    wxStaticText *Driantext = new wxStaticText(this, wxID_ANY, "No jestem gejem yyy monster hunter");
    Drian->SetFont(GetFont().Scale(2.0));
    Driansizer->Add(Drian, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    Driansizer->Add(Driantext, 0, wxALIGN_CENTER | wxBOTTOM, 10);


    wxStaticText *Kejbas = new wxStaticText(this, wxID_ANY, "Kejbas");
    wxStaticText *Kejbastext = new wxStaticText(this, wxID_ANY, "No jestem gejem yyy grzybie jebany");
    Kejbas->SetFont(GetFont().Scale(2.0));
    Kejbasizer->Add(Kejbas, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    Kejbasizer->Add(Kejbastext, 0, wxALIGN_CENTER | wxBOTTOM, 10);

    wxStaticText *Igor = new wxStaticText(this, wxID_ANY, "Igor");
    wxStaticText *Igortext = new wxStaticText(this, wxID_ANY, "No jestem heteroseksualista yyy world of goo");
    Igor->SetFont(GetFont().Scale(2.0));
    Igorsizer->Add(Igor, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    Igorsizer->Add(Igortext, 0, wxALIGN_CENTER | wxBOTTOM, 10);

    wxStaticText *Kykol = new wxStaticText(this, wxID_ANY, "Kykol");
    wxStaticText *Kykoltext = new wxStaticText(this, wxID_ANY, "No jestem gejem yyy i pedalem tez");
    Kykol->SetFont(GetFont().Scale(2.0));
    Kykolsizer->Add(Kykol, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    Kykolsizer->Add(Kykoltext, 0, wxALIGN_CENTER | wxBOTTOM, 10);

    wxButton *aboutReturnButton = new wxButton(
    this, // parent (the panel!)
        wxID_ANY, // ID
        "Powrot", // label
        wxPoint(10, 10), // position
        wxSize(100, 30) // size
    );

    aboutReturnButton->Bind(wxEVT_BUTTON, &AboutPage::OnBack, this);
    aboutSizer->Add(aboutReturnButton, 0, wxALIGN_CENTER | wxBOTTOM, 10);
}

void AboutPage::OnBack(wxCommandEvent &evt) {
    wxCommandEvent event(ABOUT_BACK);
    wxPostEvent(this, event);
}
