#include "Tile.h"

// tiletiletiletypetypethistypetypetiletiletypetiletypeempty

Tile::Tile(TileType type) {
    this->type = type;
}

Tile::Tile() : type(TileType::Empty) {
}
