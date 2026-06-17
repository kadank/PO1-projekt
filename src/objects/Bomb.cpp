#include "Bomb.h"

#include "../Board.h"
#include "../Constants.h"
#include "BombExplosion.h"

Bomb::Bomb(Board& board, Vector position) : Object(position, Vector(TILE_SIZE, TILE_SIZE), "bomb", board) {
    this->position = Vector((int)(position.x + TILE_SIZE / 2.0) / (int)TILE_SIZE * TILE_SIZE,
                            (int)(position.y + TILE_SIZE / 2.0) / (int)TILE_SIZE * TILE_SIZE);
}

void Bomb::Tick(std::set<char> pressedKeys) {
    ticks++;

    if(ticks >= 180) {
        board.objects.push_back(new BombExplosion(board, position));

        std::vector<std::pair<int, int>> directions = {
            {-TILE_SIZE, 0}, {TILE_SIZE, 0}, {0, -TILE_SIZE}, {0, TILE_SIZE}};

        for(auto [dx, dy] : directions) {
            for(int i = 1; i <= 2; i++) {
                Vector explosionPos(position.x + dx * i, position.y + dy * i);
                auto explosion = new BombExplosion(board, explosionPos);
                std::vector<Object*> collidesWith;
                TileType col = board.CheckCollisions(*explosion, &collidesWith);

                if(col == TileType::Empty || col == TileType::Destructible) {
                    board.objects.push_back(explosion);
                } else {
                    delete explosion;
                }

                if(col != TileType::Empty) {
                    break;
                }
            }
        }

        flagDelete = true;
    }
}
