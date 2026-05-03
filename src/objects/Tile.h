//
// Created by kabus on 27.04.2026.
//

#ifndef PROJEKT_TILE_H
#define PROJEKT_TILE_H
#include "Object.h"

enum class TileType {
    Solid,
    Destructible,
    Empty,
};

class Tile {
public:
    TileType type;

    Tile(TileType type);
    Tile();
};

#endif //PROJEKT_TILE_H
