//
// Created by kabus on 29.04.2026.
//

#include "Player.h"

#include "../BombermanGame.h"
#include "../Constants.h"

Player::Player() : Object(Vector(32.0, 32.0), Vector(TILE_SIZE, TILE_SIZE), "player") {
}

void Player::Tick(std::set<char> pressedKeys) {
    if(pressedKeys.contains('W')) {
        position.y -= 3;
    }
    if(pressedKeys.contains('S')) {
        position.y += 3;
    }
    if(pressedKeys.contains('A')) {
        position.x -= 3;
    }
    if(pressedKeys.contains('D')) {
        position.x += 3;
    }
}
