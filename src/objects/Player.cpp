//
// Created by kabus on 29.04.2026.
//

#include "Player.h"

#include "../BombermanGame.h"
#include "../Constants.h"

Player::Player(Board& board) : Object(Vector(32.0, 32.0), Vector(TILE_SIZE, TILE_SIZE), "player", board) {
}

void Player::Tick(std::set<char> pressedKeys) {
    if(pressedKeys.contains('W')) {
        position.y -= 3;
        if(board.CheckCollisions(*this)) {
            int oldX = position.x;
            for(int x = -8; x < 8; x++) {
                position.x = oldX + x;
                if(!board.CheckCollisions(*this)) {
                    oldX = position.x;
                    break;
                }
            }
            position.x = oldX;
        }
        while(board.CheckCollisions(*this)) {
            position.y += 1;
        }
    }
    if(pressedKeys.contains('S')) {
        position.y += 3;
        if(board.CheckCollisions(*this)) {
            int oldX = position.x;
            for(int x = -8; x < 8; x++) {
                position.x = oldX + x;
                if(!board.CheckCollisions(*this)) {
                    oldX = position.x;
                    break;
                }
            }
            position.x = oldX;
        }
        while(board.CheckCollisions(*this)) {
            position.y -= 1;
        }
    }
    if(pressedKeys.contains('A')) {
        position.x -= 3;
        if(board.CheckCollisions(*this)) {
            int oldY = position.y;
            for(int y = -8; y < 8; y++) {
                position.y = oldY + y;
                if(!board.CheckCollisions(*this)) {
                    oldY = position.y;
                    break;
                }
            }
            position.y = oldY;
        }
        while(board.CheckCollisions(*this)) {
            position.x += 1;
        }
    }
    if(pressedKeys.contains('D')) {
        position.x += 3;
        if(board.CheckCollisions(*this)) {
            int oldY = position.y;
            for(int y = -8; y < 8; y++) {
                position.y = oldY + y;
                if(!board.CheckCollisions(*this)) {
                    oldY = position.y;
                    break;
                }
            }
            position.y = oldY;
        }
        while(board.CheckCollisions(*this)) {
            position.x -= 1;
        }
    }
}
