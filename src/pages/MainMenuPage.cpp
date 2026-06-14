//
// Created by kabus on 14.06.2026.
//

#include "MainMenuPage.h"

#include <wx/clrpicker.h>

wxDEFINE_EVENT(MAIN_MENU_QUIT, wxCommandEvent);
wxDEFINE_EVENT(MAIN_MENU_NEW_GAME, wxCommandEvent);
wxDEFINE_EVENT(MAIN_MENU_ABOUT, wxCommandEvent);

MainMenuPage::MainMenuPage(wxWindow *parent) : wxPanel(parent) {
    wxBoxSizer *menuOuterSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *menuSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText *title = new wxStaticText(this, wxID_ANY, "BomberMan");
    title->SetFont(GetFont().Scale(3.0));
    menuSizer->Add(title, 0, wxALIGN_CENTER | wxBOTTOM, 10);

    wxBoxSizer* colorPickerSizer = new wxBoxSizer(wxHORIZONTAL);
    auto colorPickerLabel = new wxStaticText(this, wxID_ANY, "Kolor postaci: ");
    colorPickerSizer->Add(colorPickerLabel, 0, wxALIGN_CENTER, 10);
    characterColorPicker = new wxColourPickerCtrl(this, wxID_ANY);
    colorPickerSizer->Add(characterColorPicker, 1, 0, 10);
    menuSizer->Add(colorPickerSizer, 0, wxEXPAND | wxBOTTOM, 10);
    wxButton *newGameButton = new wxButton(
        this, // parent (the panel!)
        wxID_ANY, // ID
        "Nowa gra", // label
        wxPoint(10, 10), // position
        wxSize(100, 30) // size
    );
    newGameButton->Bind(wxEVT_BUTTON, &MainMenuPage::OnNewGame, this);
    menuSizer->Add(newGameButton, 0, wxEXPAND | wxBOTTOM, 10);
    wxButton *aboutButton = new wxButton(
        this, // parent (the panel!)
        wxID_ANY, // ID
        "O autorach", // label
        wxPoint(10, 10), // position
        wxSize(100, 30) // size
    );
    aboutButton->Bind(wxEVT_BUTTON, &MainMenuPage::OnAbout, this);
    menuSizer->Add(aboutButton, 0, wxEXPAND | wxBOTTOM, 10);
    wxButton *quitButton = new wxButton(
        this, // parent (the panel!)
        wxID_ANY, // ID
        wxT("Wyjdź z gry"), // label
        wxPoint(10, 10), // position
        wxSize(100, 30) // size
    );

    quitButton->Bind(wxEVT_BUTTON, &MainMenuPage::OnExit, this);
    menuSizer->Add(quitButton, 0, wxEXPAND);
    menuOuterSizer->AddStretchSpacer(1);
    menuOuterSizer->Add(menuSizer, 0, wxALIGN_CENTER);
    menuOuterSizer->AddStretchSpacer(1);

    SetSizer(menuOuterSizer);
}

void MainMenuPage::OnExit(wxCommandEvent &evt) {
    wxCommandEvent event(MAIN_MENU_QUIT);
    wxPostEvent(this, event);
}

void MainMenuPage::OnNewGame(wxCommandEvent &evt) {
    wxCommandEvent event(MAIN_MENU_NEW_GAME);
    event.SetInt(characterColorPicker->GetColour().GetRGB());
    wxPostEvent(this, event);
}

void MainMenuPage::OnAbout(wxCommandEvent &evt) {
    wxCommandEvent event(MAIN_MENU_ABOUT);
    wxPostEvent(this, event);
}
