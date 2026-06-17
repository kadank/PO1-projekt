#ifndef PROJEKT_TILE_H
#define PROJEKT_TILE_H

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

#endif // PROJEKT_TILE_H
