//
// Created by kabus on 14.06.2026.
//

#ifndef PROJEKT_GAMEPAGE_H
#define PROJEKT_GAMEPAGE_H

#include <wx/wx.h>
#include "../components/BombermanGame.h"
#include "../components/HudDisplay.h"

class GamePage : public wxPanel {
private:
    BombermanGame* gamePanel;
    Board board;
    HudDisplay* score;
    HudDisplay* timeLeft;
    HudDisplay* lives;
    wxPanel* overlay;
    wxStaticText* overlayTitle;
    wxStaticText* overlayDescription;
    wxButton* overlayButtonLeft;
    wxButton* overlayButtonRight;
    std::function<void()> overlayLeftButtonAction;
    std::function<void()> overlayRightButtonAction;

    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);
    void OnParentSizeChanged(wxSizeEvent& event);
    void OnOverlayLeftButtonPressed(wxCommandEvent& event);
    void OnOverlayRightButtonPressed(wxCommandEvent& event);

public:
    GamePage(wxWindow* parent);
    void Reset();
    void SetPlayerColor(wxColor color);
    void ShowOverlay(wxString title, wxString description, wxString leftButtonText, std::function<void()> leftButtonAction, wxString rightButtonText, std::function<void()> rightButtonAction);
};



#endif //PROJEKT_GAMEPAGE_H
