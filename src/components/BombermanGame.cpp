#include "BombermanGame.h"

#include "../Board.h"
#include "../objects/Enemy.h"
#include <vector>
#include <wx/dcbuffer.h>
#include <wx/graphics.h>

BombermanGame::BombermanGame(wxWindow* parent, Board& initialBoard)
    : wxPanel(parent), board(initialBoard), renderer(initialBoard) {
    Bind(wxEVT_PAINT, &BombermanGame::OnPaint, this);
    Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&) {});
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    drawTimer.Bind(wxEVT_TIMER, &BombermanGame::OnDrawTimer, this);
    drawTimer.Start(16); // ~60 FPS
}

void BombermanGame::Tick() {
    for(size_t i = 0; i < board.objects.size(); i++) {
        board.objects[i]->Tick(pressedKeys);
    }
    for(auto iter = board.objects.begin(); iter != board.objects.end();) {
        if((*iter)->flagDelete) {
            delete *iter;
            iter = board.objects.erase(iter);
        } else {
            ++iter;
        }
    }
    board.timeLeftTicks--;
    board.updateHud();

    if(board.timeLeftTicks <= 0) {
        board.KillPlayer(DeathType::Timeout);
    }

    if(pressedKeys.contains(']')) {
        for(Object* obj : board.objects) {
            if(dynamic_cast<Enemy*>(obj) != nullptr) {
                obj->flagDelete = true;
            }
        }
    }
    if(pressedKeys.contains('R')) {
        board.Restart();
    }

    int enemyCount = 0;
    for(Object* obj : board.objects) {
        if(dynamic_cast<Enemy*>(obj) != nullptr) {
            enemyCount++;
        }
    }
    if(enemyCount == 0) {
        board.showOverlay(wxT("Zwycięstwo"), "", wxT("Powrót do menu"), this->board.onMainMenu, wxT("Następny poziom"),
                          [this] {
                              board.NextLvl();
                              board.Unpause();
                          });
        board.Pause();
    }
}

void BombermanGame::OnDrawTimer(wxTimerEvent& event) {
    if(pressedKeys.contains('P') && pause_delay <= 0) {
        if(board.CheckPause()) {
            board.Unpause();
        } else {
            board.Pause();
        }

        pause_delay = 20;
    }
    if(!board.CheckPause()) Tick();
    pause_delay--;
    Refresh(false);
}

void BombermanGame::OnPaint(wxPaintEvent& event) {
    wxAutoBufferedPaintDC dc(this);
    wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

    if(frames_count == 0) Setup(gc);

    renderer.DrawFrame(gc, GetSize());

    delete gc;
}

void BombermanGame::Setup(wxGraphicsContext* gc) {

    wxFont tmpFont16(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
    fontWhite16 = gc->CreateFont(tmpFont16, *wxWHITE);
}

void BombermanGame::SetBoard(Board& board) {
    this->board = board;
    this->renderer.SetBoard(board);
}

void BombermanGame::SetKeyDown(char key) {
    pressedKeys.insert(key);
}

void BombermanGame::SetKeyUp(char key) {
    pressedKeys.erase(key);
}

void BombermanGame::SetPlayerColor(wxColour color) {
    renderer.SetPlayerColor(color);
}

void BombermanGame::ResetBoard() {
    this->board.Restart();
}
