//
// Created by kabus on 29.04.2026.
//

#ifndef PROJEKT_BOMBERMANCANVAS_H
#define PROJEKT_BOMBERMANCANVAS_H
#include <wx/graphics.h>
#include <wx/wx.h>

#define TILE_SIZE 32.0

class Board;

class BombermanCanvas: public wxPanel {
public:
    BombermanCanvas(wxWindow* parent);

    void SetBoard(Board* board);

private:
    wxTimer drawTimer;
    wxGraphicsFont fontWhite16;
    int frames_count = 0;
    Board* board;

    void OnDrawTimer(wxTimerEvent& event);
    void OnPaint(wxPaintEvent& event);

    void Setup(wxGraphicsContext* gc);
    void DrawBoard(wxGraphicsContext* gc);
    void DrawObjects(wxGraphicsContext* gc);
};

#endif //PROJEKT_BOMBERMANCANVAS_H
