#include <wx/clrpicker.h>
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <wx/wx.h>

#include "Board.h"
#include "components/BombermanGame.h"
#include "pages/AboutPage.h"
#include "pages/GamePage.h"
#include "pages/MainMenuPage.h"

enum {
    ID_NewGame,
    ID_FullScreen
};

class BombermanFrame : public wxFrame {
public:
    BombermanFrame() : wxFrame(NULL, wxID_ANY, "Bomberman", wxDefaultPosition, wxSize(800, 600)), board(21, 11) {
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        wxMenu* menuGame = new wxMenu;
        menuGame->Append(ID_NewGame, wxString::FromUTF8("Menu główne"));
        Bind(wxEVT_MENU, &BombermanFrame::OnMainMenu, this, ID_NewGame);
        menuGame->Append(ID_FullScreen, wxString::FromUTF8("Pełny ekran\tF11"), "", true);
        Bind(wxEVT_MENU, &BombermanFrame::OnToggleFullscreen, this, ID_FullScreen);

        wxMenu* menuHelp = new wxMenu;
        menuHelp->Append(wxID_ABOUT, "O autorach");
        Bind(wxEVT_MENU, &BombermanFrame::OnAbout, this, wxID_ABOUT);

        wxMenuBar* menuBar = new wxMenuBar;
        menuBar->Append(menuGame, "&Gra");
        menuBar->Append(menuHelp, "&Informacje");

        SetMenuBar(menuBar);

        menuPanel = new MainMenuPage(this);
        menuPanel->Bind(MAIN_MENU_NEW_GAME, &BombermanFrame::OnNewGame, this);
        menuPanel->Bind(MAIN_MENU_ABOUT, &BombermanFrame::OnAbout, this);
        menuPanel->Bind(MAIN_MENU_QUIT, &BombermanFrame::OnExit, this);

        aboutPanel = new AboutPage(this);

        aboutPanel->Bind(ABOUT_BACK, &BombermanFrame::OnAboutReturn, this);

        gamePanel = new GamePage(this);
        gamePanel->Bind(GAME_MENU, &BombermanFrame::OnMainMenu, this);
        // gamePanel->SetBoard(board);

        sizer->Add(menuPanel, 1, wxEXPAND);
        sizer->Add(gamePanel, 1, wxEXPAND);
        sizer->Add(aboutPanel, 1, wxEXPAND);

        SetSizer(sizer);

        gamePanel->Hide();
        aboutPanel->Hide();
    }

private:
    MainMenuPage* menuPanel;
    AboutPage* aboutPanel;
    GamePage* gamePanel;
    Board board;
    wxColourPickerCtrl* characterColorPicker;

    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event) {
        Close();
    }
    void OnAbout(wxCommandEvent& event) {
        menuPanel->Hide();
        gamePanel->Hide();
        aboutPanel->Show();
        this->Layout();
        // wxMessageBox("Autorzy \n Jakub Sakra \n Igor Lachowski \n Adrian Kisielewski \n Kacper 'Kykol' Kotulski",
        // "About Us", wxOK | wxICON_INFORMATION);
    }
    void OnMainMenu(wxCommandEvent& event) {
        gamePanel->Hide();
        aboutPanel->Hide();
        menuPanel->Show();
    }
    void OnNewGame(wxCommandEvent& event) {
        gamePanel->SetPlayerColor(event.GetInt());
        menuPanel->Hide();
        gamePanel->Show();
        aboutPanel->Hide();
        gamePanel->SetFocus();
        gamePanel->Reset();
        GetSizer()->Layout();
    }
    void OnToggleFullscreen(wxCommandEvent& event) {
        this->ShowFullScreen(!this->IsFullScreen());
    }

    void OnAboutReturn(wxCommandEvent& event) {
        menuPanel->Show();
        aboutPanel->Hide();
        this->Layout();
    }
};

class BombermanApp : public wxApp {
public:
    virtual bool OnInit() {
        wxInitAllImageHandlers(); // fuck windows
        wxFont::AddPrivateFont("assets/fonts/PxPlus_ToshibaSat_8x16.ttf");
        BombermanFrame* frame = new BombermanFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(BombermanApp);
