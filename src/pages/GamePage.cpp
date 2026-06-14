//
// Created by kabus on 14.06.2026.
//

#include "GamePage.h"

#include "../components/HudDisplay.h"

GamePage::GamePage(wxWindow *parent) : wxPanel(parent), board(21, 11) {
    SetBackgroundColour(wxColor(0, 0, 0));

    wxBoxSizer* gameSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(gameSizer);

    wxBoxSizer* hudSizer = new wxBoxSizer(wxHORIZONTAL);
    gameSizer->Add(hudSizer, 0, wxEXPAND);
    score = new HudDisplay(this, "Wynik", "0");
    hudSizer->Add(score, 1);
    timeLeft = new HudDisplay(this, "Czas", "3:00");
    hudSizer->Add(timeLeft, 1);
    lives = new HudDisplay(this, wxT("Życia"), "3");
    hudSizer->Add(lives, 1);

    board.onScoreChanged = [this](int score) {
        this->score->SetValue(wxString::Format("%d", score));
    };
    board.onLivesChanged = [this](int lives) {
        this->lives->SetValue(wxString::Format("%d", lives));
    };
    board.onTimeChanged = [this](int time) {
        this->timeLeft->SetValue(wxString::Format("%d:%02d", time/60, time%60));
    };

    gamePanel = new BombermanGame(this, board);
    gameSizer->Add(gamePanel, 1, wxEXPAND);
    gamePanel->Bind(wxEVT_KEY_DOWN, &GamePage::OnKeyDown, this);
    gamePanel->Bind(wxEVT_KEY_UP, &GamePage::OnKeyUp, this);
}

void GamePage::OnKeyDown(wxKeyEvent &event) {
    gamePanel->SetKeyDown(event.GetUnicodeKey());
    event.Skip();
}

void GamePage::OnKeyUp(wxKeyEvent &event) {
    gamePanel->SetKeyUp(event.GetUnicodeKey());
    event.Skip();
}

void GamePage::Reset() {
    gamePanel->ResetBoard();
}

void GamePage::SetPlayerColor(wxColour color) {
    gamePanel->SetPlayerColor(color);
}
