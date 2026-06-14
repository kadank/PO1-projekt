//
// Created by kabus on 27.04.2026.
//

#ifndef PROJEKT_BOARD_H
#define PROJEKT_BOARD_H
#include <list>
#include <vector>

#include "objects/Tile.h"

class Board {
public:
    std::vector<std::vector<Tile>> tiles;
    std::vector<Object*> objects;

    int width, height;

    Board(int width, int height);

    void Reset();
    TileType CheckCollisions(Object &object, std::vector<Object*>* collidesWith);
    TileType CheckCollisions(Object &object);
    bool CheckCollisionsSimple(Object &object);

private:

    void GenerateBoard();
    void SpawnEnemies();
};

#endif //PROJEKT_BOARD_H
