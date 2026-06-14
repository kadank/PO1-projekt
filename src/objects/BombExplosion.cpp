//
// Created by kabus on 14.06.2026.
//

#include "BombExplosion.h"

#include "../Board.h"

BombExplosion::BombExplosion(Board& board, Vector position) : Object(position, Vector(TILE_SIZE, TILE_SIZE), "explosion", board) {
    this->position = Vector((int)(position.x + TILE_SIZE / 2.0) / (int)TILE_SIZE * TILE_SIZE,  (int)(position.y + TILE_SIZE / 2.0) / (int)TILE_SIZE * TILE_SIZE);
}

void BombExplosion::Tick(std::set<char> pressedKeys) {
    ticks++;

    int row = position.y / TILE_SIZE;
    int col = position.x / TILE_SIZE;
    board.tiles[row][col].type = TileType::Empty;

    if(ticks >= 20) {
        flagDelete = true;
    }
}
