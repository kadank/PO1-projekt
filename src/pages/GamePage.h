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

    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);

public:
    GamePage(wxWindow* parent);
    void Reset();
    void SetPlayerColor(wxColor color);
};



#endif //PROJEKT_GAMEPAGE_H
