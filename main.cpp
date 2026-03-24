#include <iostream>
#include <wx/wx.h>
#include <wx/graphics.h>

class BombermanCanvas : public wxPanel {
public:
    BombermanCanvas(wxWindow* parent) : wxPanel(parent) {
        Bind(wxEVT_PAINT, &BombermanCanvas::OnPaint, this);
    }

private:
    void OnPaint(wxPaintEvent& event)
    {
        wxPaintDC dc(this); // required!

        wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
        if (!gc) return;

        // Drawing example

        gc->SetBrush(*wxBLACK_BRUSH);
        gc->DrawRectangle(0, 0, this->m_width, this->m_height);

        wxFont font(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
        wxGraphicsFont gfont = gc->CreateFont(font, *wxWHITE);
        gc->SetFont(gfont);
        gc->DrawText("Bomberman", this->m_width/2, this->m_height/2);

        delete gc;
    }
};

enum
{
    ID_NewGame = 1
};

class BombermanFrame : public wxFrame {
public:
    BombermanFrame() : wxFrame(NULL, wxID_ANY, "Bomberman") {
        wxMenu* menuGame = new wxMenu;
        menuGame->Append(ID_NewGame, "Nowa gra");

        wxMenu *menuHelp = new wxMenu;
        menuHelp->Append(wxID_ABOUT, "O autorach");

        wxMenuBar *menuBar = new wxMenuBar;
        menuBar->Append(menuGame, "&Gra");
        menuBar->Append(menuHelp, "&Informacje");

        SetMenuBar(menuBar);

        BombermanCanvas* canvas = new BombermanCanvas(this);

        Bind(wxEVT_MENU, &BombermanFrame::OnAbout, this, wxID_ABOUT);
    }

private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event) {
        wxMessageBox("This is a wxWidgets Hello World example",
             "About Hello World", wxOK | wxICON_INFORMATION);
    }
};

class BombermanApp : public wxApp {
public:
    virtual bool OnInit() {
        BombermanFrame *frame = new BombermanFrame();
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(BombermanApp);