#include "Board.h"

#include <algorithm>
#include <cmath>
#include <map>
#include <random>
#include <vector>
#include <wx/string.h>

#include "Constants.h"
#include "components/BombermanGame.h"
#include "objects/Enemy.h"
#include "objects/Object.h"
#include "objects/Player.h"
#include "objects/Tile.h"

Board::Board(int width, int height) {
    this->width = width;
    this->height = height;

    Restart();
}

// reset planszy
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

// zmiana wartości na kolejny poziom
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

    // mapa posiadająca informacje o sposobie przegranej
    std::map<DeathType, wxString> messages = {{DeathType::Timeout, wxT("Skończył ci się czas")},
                                              {DeathType::Enemy, wxT("Dałeś się złapać")},
                                              {DeathType::Explosion, wxT("Wysadziłeś samego siebie")},
                                              {DeathType::Final, wxT("To było twoje ostatnie życie")}};

    // wyświetlenie informacje o przegranej
    showOverlay(type == DeathType::Final ? wxT("Game Over") : wxT("Przegrana"), messages[type], wxT("Powrót do menu"),
                this->onMainMenu, wxT("Spróbuj ponownie"), [this] {
                    Respawn();
                    SetPause(false);
                });

    SetPause(true);
}

// pauza
void Board::SetPause(bool state) {
    isPaused = state;
}

// nadal pauza
bool Board::IsPaused() {
    return isPaused;
}

std::mt19937 Board::rng{std::random_device{}()};

void Board::GenerateBoard() {
    std::uniform_int_distribution<std::mt19937::result_type> rand(1, 4);
    for(int row = 0; row < height; row++) {
        if(tiles[row].capacity() < width) tiles[row].resize(width);

        for(int col = 0; col < width; col++) {
            if(col == 0 || col == width - 1 || row == 0 || row == height - 1) {
                this->tiles[row][col] = Tile(TileType::Solid);
            } else if((col + 2) % 2 == 0 && (row + 2) % 2 == 0) {
                this->tiles[row][col] = Tile(TileType::Solid);
            } else if(rand(rng) == 1 && !(row <= 2 && col <= 2)) {
                this->tiles[row][col] = Tile(TileType::Destructible);
            }
        }
    }
}

// logika rozmieszczania przeciwników
void Board::SpawnEnemies() {
    int enemyCount = 2 + 2 * level;
    std::uniform_int_distribution<std::mt19937::result_type> rand(1, 10);
    std::vector<std::pair<int, int>> emptyTiles;
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            if(tiles[y][x].type == TileType::Empty) {
                emptyTiles.push_back({x, y});
            }
        }
    }
    std::vector<int> randomIndices;
    for(int i = 0; i < emptyTiles.size(); i++) {
        randomIndices.push_back(i);
    }
    std::shuffle(randomIndices.begin(), randomIndices.end(), rng);
    for(int i = 0; i < enemyCount; i++) {
        if(emptyTiles[randomIndices[i]].first < 4 && emptyTiles[randomIndices[i]].second < 4) {
            enemyCount++;
            continue;
        }

        objects.push_back(new Enemy(*this, Vector(TILE_SIZE * emptyTiles[randomIndices[i]].first,
                                                  TILE_SIZE * emptyTiles[randomIndices[i]].second)));
    }
}

TileType Board::CheckCollisions(Object& object, std::vector<Object*>* collidesWith) {
    TileType out = TileType::Empty;
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
    // sprawdza kolizje wokół danego punktu
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
