#include "GamePage.h"

#include "../components/HudDisplay.h"

wxDEFINE_EVENT(GAME_MENU, wxCommandEvent);

GamePage::GamePage(wxWindow* parent) : wxPanel(parent), board(21, 11) {
    SetBackgroundColour(wxColor(60, 80, 60));

    wxBoxSizer* gameSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(gameSizer);

    wxBoxSizer* hudSizer = new wxBoxSizer(wxHORIZONTAL);
    gameSizer->Add(hudSizer, 0, wxEXPAND);
    score = new HudDisplay(this, "Wynik", "0");
    hudSizer->Add(score, 1);
    level = new HudDisplay(this, "Poziom", "1");
    hudSizer->Add(level, 1);
    timeLeft = new HudDisplay(this, "Czas", "3:00");
    hudSizer->Add(timeLeft, 1);
    lives = new HudDisplay(this, wxT("Życia"), "3");
    hudSizer->Add(lives, 1);

    board.updateHud = [this]() {
        this->score->SetValue(wxString::Format("%d", board.score));
        this->level->SetValue(wxString::Format("%d", board.level));
        this->timeLeft->SetValue(
            wxString::Format("%d:%02d", board.timeLeftTicks / 60 / 60, board.timeLeftTicks / 60 % 60));
        this->lives->SetValue(wxString::Format("%d", board.lives));
    };
    board.showOverlay = [this](wxString title, wxString description, wxString leftButtonText,
                               std::function<void()> leftButtonAction, wxString rightButtonText,
                               std::function<void()> rightButtonAction) {
        this->ShowOverlay(title, description, leftButtonText, leftButtonAction, rightButtonText, rightButtonAction);
    };
    board.hideOverlay = [this]() { this->HideOverlay(); };
    board.onMainMenu = [this]() { this->OnMenu(); };

    gamePanel = new BombermanGame(this, board);
    gameSizer->Add(gamePanel, 1, wxEXPAND);
    gamePanel->Bind(wxEVT_KEY_DOWN, &GamePage::OnKeyDown, this);
    gamePanel->Bind(wxEVT_KEY_UP, &GamePage::OnKeyUp, this);

    gamePanel->Bind(wxEVT_SIZE, &GamePage::OnParentSizeChanged, this);

    overlay = new wxPanel(this);
    overlay->SetBackgroundColour(wxColor(0, 0, 0, 128));
    overlay->SetPosition(GetPosition());
    overlay->SetSize(GetSize());
    overlay->Raise();
    overlay->Hide();

    wxBoxSizer* overlaySizerOuter = new wxBoxSizer(wxVERTICAL);
    overlay->SetSizer(overlaySizerOuter);
    wxBoxSizer* overlaySizer = new wxBoxSizer(wxVERTICAL);
    overlaySizerOuter->AddStretchSpacer(1);
    overlaySizerOuter->Add(overlaySizer, 0, wxALIGN_CENTER);
    overlaySizerOuter->AddStretchSpacer(1);

    overlayTitle = new wxStaticText(overlay, wxID_ANY, wxT("Przejebałeś"));
    overlayTitle->SetFont(GetFont().Scale(3.0));
    overlaySizer->Add(overlayTitle, 0, wxALIGN_CENTER);
    overlayDescription = new wxStaticText(overlay, wxID_ANY, wxT("Jesteś zjebem i chuj."));
    overlaySizer->Add(overlayDescription, 0, wxALIGN_CENTER | wxBOTTOM, 15);

    wxGridSizer* overlayButtonSizer = new wxGridSizer(wxHORIZONTAL);
    overlayButtonSizer->SetCols(2);
    overlaySizer->Add(overlayButtonSizer, 0, wxALIGN_CENTER);
    overlayButtonLeft = new wxButton(overlay, wxID_ANY, "Chuj");
    overlayButtonLeft->Bind(wxEVT_BUTTON, &GamePage::OnOverlayLeftButtonPressed, this);
    overlayButtonSizer->Add(overlayButtonLeft, 1, wxRIGHT, 10);
    overlayButtonRight = new wxButton(overlay, wxID_ANY, "Dupa");
    overlayButtonRight->Bind(wxEVT_BUTTON, &GamePage::OnOverlayRightButtonPressed, this);
    overlayButtonSizer->Add(overlayButtonRight, 1);
}

void GamePage::ShowOverlay(wxString title, wxString description, wxString leftButtonText,
                           std::function<void()> leftButtonAction, wxString rightButtonText,
                           std::function<void()> rightButtonAction) {
    overlayTitle->SetLabel(title);
    overlayDescription->SetLabel(description);
    overlayButtonLeft->SetLabel(leftButtonText);
    overlayButtonRight->SetLabel(rightButtonText);
    overlayLeftButtonAction = leftButtonAction;
    overlayRightButtonAction = rightButtonAction;
    overlay->Show();
}

void GamePage::HideOverlay() {
    overlay->Hide();
}

void GamePage::OnOverlayLeftButtonPressed(wxCommandEvent& event) {
    overlay->Hide();
    overlayLeftButtonAction();
}

void GamePage::OnOverlayRightButtonPressed(wxCommandEvent& event) {
    overlay->Hide();
    overlayRightButtonAction();
}

void GamePage::OnParentSizeChanged(wxSizeEvent& event) {
    overlay->SetSize(GetSize());
}

void GamePage::OnKeyDown(wxKeyEvent& event) {
    gamePanel->SetKeyDown(event.GetUnicodeKey());
    event.Skip();
}

void GamePage::OnKeyUp(wxKeyEvent& event) {
    gamePanel->SetKeyUp(event.GetUnicodeKey());
    event.Skip();
}

void GamePage::Reset() {
    gamePanel->ResetBoard();
}

void GamePage::SetPlayerColor(wxColour color) {
    gamePanel->SetPlayerColor(color);
}

void GamePage::OnMenu() {
    wxCommandEvent event(GAME_MENU);
    wxPostEvent(this, event);
}
