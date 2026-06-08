#include <iostream>
#include <optional>
#include <random>
#include <wx/wx.h>
#include <wx/graphics.h>
#include <wx/dcbuffer.h>

#include "Board.h"
#include "BombermanGame.h"

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

enum
{
    ID_NewGame,
    ID_FullScreen
};

class BombermanFrame : public wxFrame {
public:
    BombermanFrame() : wxFrame(NULL, wxID_ANY, "Bomberman", wxDefaultPosition, wxSize(800, 600)), board(21, 11) {
        wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

        wxMenu *menuGame = new wxMenu;
        menuGame->Append(ID_NewGame, "Nowa gra");
        Bind(wxEVT_MENU, &BombermanFrame::OnNewGame, this, ID_NewGame);
        menuGame->Append(ID_FullScreen, wxString::FromUTF8("Pełny ekran\tF11"), "", true);
        Bind(wxEVT_MENU, &BombermanFrame::OnToggleFullscreen, this, ID_FullScreen);

        wxMenu *menuHelp = new wxMenu;
        menuHelp->Append(wxID_ABOUT, "O autorach");
        Bind(wxEVT_MENU, &BombermanFrame::OnAbout, this, wxID_ABOUT);

        wxMenuBar *menuBar = new wxMenuBar;
        menuBar->Append(menuGame, "&Gra");
        menuBar->Append(menuHelp, "&Informacje");

        SetMenuBar(menuBar);

        menuPanel = new wxPanel(this);
        wxBoxSizer *menuOuterSizer = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer *menuSizer = new wxBoxSizer(wxVERTICAL);
        wxStaticText *title = new wxStaticText(menuPanel, wxID_ANY, "BomberMan");
        title->SetFont(GetFont().Scale(3.0));
        menuSizer->Add(title, 0, wxALIGN_CENTER | wxBOTTOM, 10);
        wxButton *newGameButton = new wxButton(
            menuPanel, // parent (the panel!)
            wxID_ANY, // ID
            "Nowa gra", // label
            wxPoint(10, 10), // position
            wxSize(100, 30) // size
        );
        newGameButton->Bind(wxEVT_BUTTON, &BombermanFrame::OnNewGame, this);
        menuSizer->Add(newGameButton, 0, wxEXPAND | wxBOTTOM, 10);
        wxButton *aboutButton = new wxButton(
            menuPanel, // parent (the panel!)
            wxID_ANY, // ID
            "O autorach", // label
            wxPoint(10, 10), // position
            wxSize(100, 30) // size
        );
        aboutButton->Bind(wxEVT_BUTTON, &BombermanFrame::OnAbout, this);
        menuSizer->Add(aboutButton, 0, wxEXPAND | wxBOTTOM, 10);
        wxButton *quitButton = new wxButton(
            menuPanel, // parent (the panel!)
            wxID_ANY, // ID
            wxT("Wyjdź z gry"), // label
            wxPoint(10, 10), // position
            wxSize(100, 30) // size
        );
        quitButton->Bind(wxEVT_BUTTON, &BombermanFrame::OnExit, this);
        menuSizer->Add(quitButton, 0, wxEXPAND);
        menuOuterSizer->AddStretchSpacer(1);
        menuOuterSizer->Add(menuSizer, 0, wxALIGN_CENTER);
        menuOuterSizer->AddStretchSpacer(1);

        menuPanel->SetSizer(menuOuterSizer);

        gamePanel = new BombermanGame(this, board);
        // gamePanel->SetBoard(board);

        sizer->Add(menuPanel, 1, wxEXPAND);
        sizer->Add(gamePanel, 1, wxEXPAND);

        SetSizer(sizer);

        gamePanel->Hide();
        gamePanel->Bind(wxEVT_KEY_DOWN, &BombermanFrame::OnKeyDown, this);
        gamePanel->Bind(wxEVT_KEY_UP, &BombermanFrame::OnKeyUp, this);

    }

private:
    wxPanel* menuPanel;
    BombermanGame* gamePanel;
    Board board;

    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event) {
        Close();
    }
    void OnAbout(wxCommandEvent& event) {
        wxMessageBox("This is a wxWidgets Hello World example",
             "About Hello World", wxOK | wxICON_INFORMATION);
    }
    void OnNewGame(wxCommandEvent &event) {
        menuPanel->Hide();
        gamePanel->Show();
        gamePanel->SetFocus();
        board.Reset();
        GetSizer()->Layout();
    }
    void OnToggleFullscreen(wxCommandEvent &event) {
        this->ShowFullScreen(!this->IsFullScreen());
    }

    void OnKeyDown(wxKeyEvent& event) {
        gamePanel->SetKeyDown(event.GetUnicodeKey());
        event.Skip();
    }

    void OnKeyUp(wxKeyEvent& event) {
        gamePanel->SetKeyUp(event.GetUnicodeKey());
        event.Skip();
    }
};

class BombermanApp : public wxApp {
public:
    virtual bool OnInit() {
        wxInitAllImageHandlers(); // fuck windows
        BombermanFrame *frame = new BombermanFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(BombermanApp);