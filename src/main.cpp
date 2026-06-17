#include <iostream>
#include <optional>
#include <random>
#include <wx/clrpicker.h>
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <wx/wx.h>

#include "Board.h"
#include "components/BombermanGame.h"
#include "pages/AboutPage.h"
#include "pages/GamePage.h"
#include "pages/MainMenuPage.h"

/*class BombermanCanvas : public wxPanel {
public:
    BombermanCanvas(wxWindow* parent) : wxPanel(parent) {
        Bind(wxEVT_PAINT, &BombermanCanvas::OnPaint, this);
        Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&) {});
        SetBackgroundStyle(wxBG_STYLE_PAINT);

        refreshTimer.Bind(wxEVT_TIMER, &BombermanCanvas::OnRefreshTimer, this);
        refreshTimer.Start(14); // ~60 FPS
    }

private:
    wxGraphicsFont gfont30;
    int pos;

    void OnPaint(wxPaintEvent& event)
    {
        wxAutoBufferedPaintDC dc(this); // required!

        wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
        if (!gc) return;

        // Drawing example

        if(gfont30.IsNull()) {
            wxFont font(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
            gfont30 = gc->CreateFont(font, *wxWHITE);
        }

        gc->SetBrush(*wxBLACK_BRUSH);
        gc->DrawRectangle(0, 0, this->GetSize().GetWidth(), this->GetSize().GetHeight());

        gc->SetFont(gfont30);
        gc->DrawText("Bomberman", this->GetSize().GetWidth()/2, this->GetSize().GetHeight()/2 - pos);
        pos += 2;
        pos = pos % 100;

        delete gc;
    }

    wxTimer refreshTimer;

    void OnRefreshTimer(wxTimerEvent&) {
        Refresh(false);
    }
};*/

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
