#include "Board.h"

#include <iostream>
#include <list>
#include <random>

#include "Constants.h"
#include "components/BombermanGame.h"
#include "objects/Enemy.h"
#include "objects/Player.h"

Board::Board(int width, int height) {
    this->width = width;
    this->height = height;

    Restart();
}

void Board::Reset() {
    tiles.clear();
    tiles.resize(height);
    objects.clear();
    objects.push_back(new Player(*this));
    timeLeftTicks = 180 * 60;
    GenerateBoard();
    SpawnEnemies();
    Unpause();
    if(hideOverlay) hideOverlay();
}
void Board::Restart() {
    level = 1;
    score = 0;
    lives = 3;
    oldScore = 0;
    if (onLivesChanged)onLivesChanged(lives);
    if (onScoreChanged)onScoreChanged(score);
    Reset();
}

void Board::Respawn() {
    lives--;
    if(lives <= 0) {
        Restart();
        return;
    }
    score = oldScore;
    if (onLivesChanged)onLivesChanged(lives);
    if (onScoreChanged)onScoreChanged(score);
    Reset();
}

int Board::CheckLvl() {
    return level;
}

void Board::NextLvl() {
    level++;
    oldScore = score;
    Reset();
}

void Board::Pause() {
    is_paused = true;
}

void Board::Unpause() {
    is_paused = false;
}

bool Board::CheckPause() {
    if(is_paused) return true;
    return false;
}

void Board::GenerateBoard() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> rand(1, 5);

    for(int row = 0; row < height; row++) {
        if(tiles[row].capacity() < width) tiles[row].resize(width);

        for(int col = 0; col < width; col++) {
            if(row == 1 && col == 1 || row == 1 && col == 2 || row == 2 && col == 1) continue;

            if(col == 0 || col == width - 1 || row == 0 || row == height - 1) {
                this->tiles[row][col] = Tile(TileType::Solid);
            } else if((col + 2) % 2 == 0 && (row + 2) % 2 == 0) {
                this->tiles[row][col] = Tile(TileType::Solid);
            } else if(rand(rng) == 1) {
                this->tiles[row][col] = Tile(TileType::Destructible);
            }
        }
    }
}

void Board::SpawnEnemies() {
    int enemycount = 2 + 2 * level;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> rand(1, 10);
    do {
        for(int row = 0; row < height; row++) {
            for(int col = 0; col < width; col++) {
                if(row == 1 && col < 6 || col == 1 && row < 6) continue;
                if(tiles[row][col].type == TileType::Empty && enemycount > 0 && rand(rng) == 1) {
                    objects.push_back(new Enemy(*this, Vector(TILE_SIZE * col, TILE_SIZE * row)));
                    enemycount--;
                }
            }
        }
    } while(enemycount > 0);
}

TileType Board::CheckCollisions(Object& object, std::vector<Object*>* collidesWith) {
    TileType out = TileType::Empty;

    /*
    return !(a.x > b.x + b.w ||
    a.x + a.w < b.x ||
    a.y > b.y + b.h ||
    a.y + a.h < b.y);
    */

    for(int row = 0; row < height; row++) {
        for(int col = 0; col < width; col++) {
            if(tiles[row][col].type != TileType::Empty) {
                if(!(object.position.x >= col * TILE_SIZE + TILE_SIZE ||
                     object.position.x + object.size.x <= col * TILE_SIZE ||
                     object.position.y >= row * TILE_SIZE + TILE_SIZE ||
                     object.position.y + object.size.y <= row * TILE_SIZE)) {
                    out = tiles[row][col].type;
                    break;
                }
            }
        }
    }

    for(auto object2 : objects) {
        if(!(object.position.x >= object2->position.x + object2->size.x ||
             object.position.x + object.size.x <= object2->position.x ||
             object.position.y >= object2->position.y + object2->size.y ||
             object.position.y + object.size.y <= object2->position.y)) {
            collidesWith->push_back(object2);
        }
    }

    return out;
}

TileType Board::CheckCollisions(Object& object) {
    return CheckCollisions(object, new std::vector<Object*>());
}

bool Board::CheckCollisionsSimple(Object& object) {
    return CheckCollisions(object, new std::vector<Object*>()) != TileType::Empty;
}
