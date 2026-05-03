//
// Created by kabus on 27.04.2026.
//

#include "Tile.h"

Tile::Tile(TileType type) {
    this->type = type;
}

Tile::Tile(): type(TileType::Empty) {}
