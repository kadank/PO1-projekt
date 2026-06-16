#include "Tile.h"

Tile::Tile(TileType type) {
    this->type = type;
}

Tile::Tile(): type(TileType::Empty) {}
