#include "Player.h"

#include "../Constants.h"
#include "../components/BombermanGame.h"
#include "Bomb.h"

Player::Player(Board& board) : Object(Vector(32.0, 32.0), Vector(TILE_SIZE, TILE_SIZE), "player", board) {
}

void Player::Tick(std::set<char> pressedKeys) {
    HandleMovement(pressedKeys, 'W', position.y, position.x, -1);
    HandleMovement(pressedKeys, 'S', position.y, position.x, 1);
    HandleMovement(pressedKeys, 'A', position.x, position.y, -1);
    HandleMovement(pressedKeys, 'D', position.x, position.y, 1);

    int bombCount = 0;
    for(auto obj : board.objects) {
        if(dynamic_cast<Bomb*>(obj) != nullptr) {
            bombCount++;
        }
    }
    if(pressedKeys.contains(' ') && bombCount == 0) {
        board.objects.push_back(new Bomb(board, position));
    }
}

bool Player::IsColliding() {
    std::vector<Object*> collidesWith;
    if(board.CheckCollisions(*this, &collidesWith) != TileType::Empty) return true;
    // blokowanie ruchu w przez bombę która ma isSolid == true
    for(auto obj : collidesWith) {
        Bomb* bomb = dynamic_cast<Bomb*>(obj);
        if(bomb != nullptr && bomb->isSolid) {
            return true;
        }
    }
    return false;
}

void Player::HandleMovement(std::set<char> pressedKeys, char key, double& moveAxis, double& offsetAxis, int moveDir) {
    if(pressedKeys.contains(key)) {
        moveAxis += moveDir * 3;
        // sprawdzenie czy da się gracza wepchnąć w boczny korytarz na siłę
        if(IsColliding()) {
            float oldOffset = offsetAxis;
            for(int offset = -8; offset < 8; offset++) {
                offsetAxis = oldOffset + offset;
                if(!IsColliding()) {
                    oldOffset = offsetAxis;
                    break;
                }
            }
            offsetAxis = oldOffset;
        }
        while(IsColliding()) {
            moveAxis -= moveDir;
        }
    }
}
