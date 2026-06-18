#include "AboutPage.h"
#include <wx/wx.h>

wxDEFINE_EVENT(ABOUT_BACK, wxCommandEvent);
// Strona wyświetlająca informacje o autorach... nie wiem co więcej powiedzieć
AboutPage::AboutPage(wxWindow* parent) : wxPanel(parent) {
    wxBoxSizer* aboutOuterSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* aboutSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* about = new wxStaticText(this, wxID_ANY, "O autorach");
    about->SetFont(GetFont().Scale(3.0));
    aboutSizer->Add(about, 0, wxALIGN_CENTER | wxBOTTOM, 10);

    aboutOuterSizer->AddStretchSpacer(1);
    aboutOuterSizer->Add(aboutSizer, 0, wxALIGN_CENTER);
    aboutOuterSizer->AddStretchSpacer(1);
    SetSizer(aboutOuterSizer);

    wxGridSizer* aboutContentSizer = new wxGridSizer(2, 2, 20, 20);
    aboutSizer->Add(aboutContentSizer, 0, wxALIGN_CENTER);

    wxBoxSizer* author1Sizer = new wxBoxSizer(wxVERTICAL);
    author1Sizer->SetMinSize(160, 100);
    aboutContentSizer->Add(author1Sizer, 0, wxALIGN_CENTER);

    wxBoxSizer* author2Sizer = new wxBoxSizer(wxVERTICAL);
    author2Sizer->SetMinSize(160, 100);
    aboutContentSizer->Add(author2Sizer, 0, wxALIGN_CENTER);

    wxBoxSizer* author3Sizer = new wxBoxSizer(wxVERTICAL);
    author3Sizer->SetMinSize(160, 100);
    aboutContentSizer->Add(author3Sizer, 0, wxALIGN_CENTER);

    wxBoxSizer* author4Sizer = new wxBoxSizer(wxVERTICAL);
    author4Sizer->SetMinSize(160, 100);
    aboutContentSizer->Add(author4Sizer, 0, wxALIGN_CENTER);

    wxStaticText* author1Name = new wxStaticText(this, wxID_ANY, "Adrian Kisielewski");
    wxStaticText* author1Text = new wxStaticText(this, wxID_ANY,
                                                 wxT("Wielki fan Warframe i serii Monster Hunter. Lubię słuchać rocka "
                                                     "z lat 80 i zajmować się zwierzętami hodowlanymi."),
                                                 wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    author1Name->SetFont(GetFont().Scale(2.0));
    author1Text->Wrap(300);
    author1Sizer->Add(author1Name, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    author1Sizer->Add(author1Text, 0, wxEXPAND, 10);

    wxStaticText* author2Name = new wxStaticText(this, wxID_ANY, "Jakub Sakra");
    wxStaticText* author2Text = new wxStaticText(this, wxID_ANY,
                                                 wxT("Lubię grać w gry komputerowe. Nie wiem co więcej tu o sobię "
                                                     "napisać. Chodzę na Politechnikę Świętokszyską"),
                                                 wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    author2Name->SetFont(GetFont().Scale(2.0));
    author2Text->Wrap(300);
    author2Sizer->Add(author2Name, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    author2Sizer->Add(author2Text, 0, wxEXPAND, 10);

    wxStaticText* author3Name = new wxStaticText(this, wxID_ANY, "Igor Lachowski");
    wxStaticText* author3Text = new wxStaticText(this, wxID_ANY,
                                                 wxT("Jeżeli chodzi o gry, to preferuję starsze tytuły z naciskiem na "
                                                     "fabułę. W wolnym czasie lubię czytać książki i słuchać muzykę."),
                                                 wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    author3Name->SetFont(GetFont().Scale(2.0));
    author3Text->Wrap(300);
    author3Sizer->Add(author3Name, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    author3Sizer->Add(author3Text, 0, wxEXPAND, 10);

    wxStaticText* author4Name = new wxStaticText(this, wxID_ANY, "Kacper Kotulski");
    wxStaticText* author4Text =
        new wxStaticText(this, wxID_ANY,
                         wxT("20 lat, w wolnym czasie zajmuje się robieniem renderów 3d oraz graniem w karty. Lubię "
                             "grywać w gry na komputerze oraz oglądać filmy"),
                         wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    author4Name->SetFont(GetFont().Scale(2.0));
    author4Text->Wrap(300);
    author4Sizer->Add(author4Name, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    author4Sizer->Add(author4Text, 0, wxEXPAND, 10);

    wxButton* aboutReturnButton = new wxButton(this, wxID_ANY, wxT("Powrót"), wxPoint(10, 10), wxSize(100, 30));

    aboutReturnButton->Bind(wxEVT_BUTTON, &AboutPage::OnBack, this);
    aboutSizer->Add(aboutReturnButton, 0, wxALIGN_CENTER | wxTOP, 20);
}

void AboutPage::OnBack(wxCommandEvent& evt) {
    wxCommandEvent event(ABOUT_BACK);
    wxPostEvent(this, event);
}
