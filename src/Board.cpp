#include "Board.h"

#include <cmath>
#include <iostream>
#include <list>
#include <random>

#include "Constants.h"
#include "components/BombermanGame.h"
#include "objects/Enemy.h"
#include "objects/Object.h"
#include "objects/Player.h"

Board::Board(int width, int height) {
    this->width = width;
    this->height = height;

    Restart();
}

void Board::Reset() {
    tiles.clear();
    tiles.resize(height);
    for(auto object : objects) {
        delete object;
    }
    objects.clear();
    objects.push_back(new Player(*this));
    timeLeftTicks = 180 * 60;
    GenerateBoard();
    SpawnEnemies();
    SetPause(false);
    if(hideOverlay) hideOverlay();
}
void Board::Restart() {
    level = 1;
    score = 0;
    lives = 3;
    oldScore = 0;
    width = 21;
    height = 11;
    if(updateHud) updateHud();
    Reset();
}

void Board::Respawn() {
    lives--;
    if(lives <= 0) {
        Restart();
        return;
    }
    score = oldScore;
    if(updateHud) updateHud();
    Reset();
}

void Board::NextLvl() {
    level++;
    oldScore = score;
    width += 2;
    height += 2;
    Reset();
}

void Board::KillPlayer(DeathType type) {
    if(lives <= 1) {
        type = DeathType::Final;
    }

    switch(type) {
        case DeathType::Timeout:
            showOverlay(wxT("Przegrana"), wxT("Skończył ci się czas"), wxT("Powrót do menu"), this->onMainMenu,
                        wxT("Spróbuj ponownie"), [this] {
                            Respawn();
                            SetPause(false);
                        });
            break;
        case DeathType::Enemy:
            showOverlay(wxT("Przegrana"), wxT("Dałeś się złapać"), wxT("Powrót do menu"), this->onMainMenu,
                        wxT("Spróbuj ponownie"), [this] {
                            Respawn();
                            SetPause(false);
                        });
            break;
        case DeathType::Explosion:
            showOverlay(wxT("Przegrana"), wxT("Wysadziłeś samego siebie"), wxT("Powrót do menu"), this->onMainMenu,
                        wxT("Spróbuj ponownie"), [this] {
                            Respawn();
                            SetPause(false);
                        });
            break;
        case DeathType::Final:
            showOverlay(wxT("Game Over"), wxT("To było twoje ostatnie życie"), wxT("Powrót do menu"), this->onMainMenu,
                        wxT("Nowa gra"), [this] {
                            Restart();
                            SetPause(false);
                        });
            break;
    }
    SetPause(true);
}

void Board::SetPause(bool state) {
    isPaused = state;
}

bool Board::IsPaused() {
    return isPaused;
}

std::mt19937 Board::rng{std::random_device{}()};

void Board::GenerateBoard() {
    std::uniform_int_distribution<std::mt19937::result_type> rand(1, 4);

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
    std::vector<Object*> tmp;
    return CheckCollisions(object, &tmp);
}

bool Board::CheckCollisionsSimple(Object& object) {
    std::vector<Object*> tmp;
    return CheckCollisions(object, &tmp) != TileType::Empty;
}

bool Board::CheckCollisionsCircle(Object& object, std::vector<Object*>* collidesWith) {
    bool out = false;

    for(auto object2 : objects) {
        if(object2 == &object) continue;
        Vector objectCenter = Vector(object.position.x + object.size.x / 2.0, object.position.y + object.size.y / 2.0);
        double objectRadius = (object.size.x + object.size.y) / 4.0;
        Vector object2Center =
            Vector(object2->position.x + object2->size.x / 2.0, object2->position.y + object2->size.y / 2.0);
        double object2Radius = (object2->size.x + object2->size.y) / 4.0;
        double distance = sqrt(pow(object2Center.x - objectCenter.x, 2) + pow(object2Center.y - objectCenter.y, 2));

        if(distance <= objectRadius + object2Radius) {
            collidesWith->push_back(object2);
            out = true;
        }
    }

    return out;
}
