//
// Created by kabus on 29.04.2026.
//

#ifndef PROJEKT_BOMBERMANCANVAS_H
#define PROJEKT_BOMBERMANCANVAS_H
#include <wx/graphics.h>
#include <wx/wx.h>
#include <set>

#include "../render/Renderer.h"

class Board;

class BombermanGame: public wxPanel {
public:
    BombermanGame(wxWindow* parent, Board& initialBoard);

    void SetBoard(Board& board);
    void SetKeyDown(char key);
    void SetKeyUp(char key);
    void SetPlayerColor(wxColor color);
    void ResetBoard();

private:
    wxTimer drawTimer;
    wxGraphicsFont fontWhite16;
    int frames_count = 0;
    Board& board;
    Renderer renderer;
    std::set<char> pressedKeys;

    void Tick();
    void OnDrawTimer(wxTimerEvent& event);
    void OnPaint(wxPaintEvent& event);

    void Setup(wxGraphicsContext* gc);
};

#endif //PROJEKT_BOMBERMANCANVAS_H
