//
// Created by kabus on 29.04.2026.
//

#include "BombermanCanvas.h"

#include <wx/dcbuffer.h>
#include <wx/graphics.h>

#include "../Board.h"

BombermanCanvas::BombermanCanvas(wxWindow *parent): wxPanel(parent) {
    Bind(wxEVT_PAINT, &BombermanCanvas::OnPaint, this);
    Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&) {});
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    drawTimer.Bind(wxEVT_TIMER, &BombermanCanvas::OnDrawTimer, this);
    drawTimer.Start(16); // ~60 FPS
}

void BombermanCanvas::OnDrawTimer(wxTimerEvent &event) {
    Refresh(false);
}

void BombermanCanvas::OnPaint(wxPaintEvent &event) {
    wxAutoBufferedPaintDC dc(this);
    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

    if(frames_count == 0) Setup(gc);

    // clear canvas
    gc->SetBrush(*wxBLACK_BRUSH);
    gc->DrawRectangle(0, 0, this->GetSize().GetWidth(), this->GetSize().GetHeight());

    DrawBoard(gc);
    DrawObjects(gc);

    delete gc;
}

void BombermanCanvas::DrawBoard(wxGraphicsContext* gc) {
    for(int row = 0; row < board->height; row++) {
        for(int col = 0; col < board->width; col++) {
            Tile* tile = &board->tiles[row][col];
            switch(tile->type) {
                case TileType::Empty:
                    gc->SetBrush(*wxBLACK_BRUSH);
                    break;
                case TileType::Solid:
                    gc->SetBrush(*wxRED_BRUSH);
                    break;
                case TileType::Destructible:
                    gc->SetBrush(*wxCYAN_BRUSH);
                    break;
            }

            gc->DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE);
        }
    }
}

void BombermanCanvas::DrawObjects(wxGraphicsContext *gc) {
    for(auto object: board->objects) {
        object->Render(gc);
    }
}

void BombermanCanvas::Setup(wxGraphicsContext* gc) {
    wxFont tmpFont16(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
    fontWhite16 = gc->CreateFont(tmpFont16, *wxWHITE);
}

void BombermanCanvas::SetBoard(Board *board) {
    this->board = board;
}
