//
// Created by kabus on 29.04.2026.
//

#include "Player.h"

#include "../render/BombermanCanvas.h"

Player::Player() : Object(Vector(32.0, 32.0), Vector(TILE_SIZE, TILE_SIZE)) {
}

void Player::Render(wxGraphicsContext *gc) {
    gc->SetBrush(*wxYELLOW_BRUSH);
    gc->DrawEllipse(position.x, position.y, size.x, size.y);
}
