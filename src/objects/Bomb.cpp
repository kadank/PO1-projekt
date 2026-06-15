//
// Created by kabus on 11.06.2026.
//

#include "Bomb.h"

#include "BombExplosion.h"
#include "../Board.h"

Bomb::Bomb(Board& board, Vector position) : Object(position, Vector(TILE_SIZE, TILE_SIZE), "bomb", board) {
    this->position = Vector((int)(position.x + TILE_SIZE / 2.0) / (int)TILE_SIZE * TILE_SIZE,  (int)(position.y + TILE_SIZE / 2.0) / (int)TILE_SIZE * TILE_SIZE);
}

void Bomb::Tick(std::set<char> pressedKeys) {
    ticks++;

    if(ticks >= 180) {
        board.objects.push_back(new BombExplosion(board, position));

        for(int x = position.x - TILE_SIZE; x >= position.x - TILE_SIZE * 2; x -= TILE_SIZE) {
            std::vector<Object*> collidesWith;
            auto explosion = new BombExplosion(board, Vector(x, position.y));
            TileType col = board.CheckCollisions(*explosion, &collidesWith);
            if(col == TileType::Empty || col == TileType::Destructible) {
                board.objects.push_back(explosion);
            }
            if(col != TileType::Empty) {
                break;
            }
        }

        for(int x = position.x + TILE_SIZE; x <= position.x + TILE_SIZE * 2; x += TILE_SIZE) {
            std::vector<Object*> collidesWith;
            auto explosion = new BombExplosion(board, Vector(x, position.y));
            TileType col = board.CheckCollisions(*explosion, &collidesWith);
            if(col == TileType::Empty || col == TileType::Destructible) {
                board.objects.push_back(explosion);
            }
            if(col != TileType::Empty) {
                break;
            }
        }

        for(int y = position.y - TILE_SIZE; y >= position.y - TILE_SIZE * 2; y -= TILE_SIZE) {
            std::vector<Object*> collidesWith;
            auto explosion = new BombExplosion(board, Vector(position.x, y));
            TileType col = board.CheckCollisions(*explosion, &collidesWith);
            if(col == TileType::Empty || col == TileType::Destructible) {
                board.objects.push_back(explosion);
            }
            if(col != TileType::Empty) {
                break;
            }
        }

        for(int y = position.y + TILE_SIZE; y <= position.y + TILE_SIZE * 2; y += TILE_SIZE) {
            std::vector<Object*> collidesWith;
            auto explosion = new BombExplosion(board, Vector(position.x, y));
            TileType col = board.CheckCollisions(*explosion, &collidesWith);
            if(col == TileType::Empty || col == TileType::Destructible) {
                board.objects.push_back(explosion);
            }
            if(col != TileType::Empty) {
                break;
            }
        }

        flagDelete = true;
    }
}
