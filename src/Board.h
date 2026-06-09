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
    bool CheckCollisions(Object &object, std::list<Object*>* collidesWith);
    bool CheckCollisions(Object &object);

private:
    void GenerateBoard();
};

#endif //PROJEKT_BOARD_H
