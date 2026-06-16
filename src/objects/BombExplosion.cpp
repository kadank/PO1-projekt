#include "BombExplosion.h"

#include "Enemy.h"
#include "../Board.h"

BombExplosion::BombExplosion(Board& board, Vector position) : Object(position, Vector(TILE_SIZE, TILE_SIZE), "explosion", board) {
    this->position = Vector((int)(position.x + TILE_SIZE / 2.0) / (int)TILE_SIZE * TILE_SIZE,  (int)(position.y + TILE_SIZE / 2.0) / (int)TILE_SIZE * TILE_SIZE);
}

void BombExplosion::Tick(std::set<char> pressedKeys) {
    ticks++;

    if (ticks ==1) {
        int row = position.y / TILE_SIZE;
        int col = position.x / TILE_SIZE;
        board.tiles[row][col].type = TileType::Empty;

        std::vector<Object*> tmp;
        board.CheckCollisions(*this, &tmp);
        for (auto obj : tmp) {
            if (dynamic_cast<Enemy*>(obj) != nullptr) {
                obj->flagDelete = true;
                board.score += 10;
                board.onScoreChanged(board.score);
            }
        }
    }

    if(ticks >= 20) {
        flagDelete = true;
    }
}
