//
// Created by kabus on 27.04.2026.
//

#include "Board.h"

#include <random>

#include "objects/Player.h"

Board::Board(int width, int height) {
    this->width = width;
    this->height = height;

    Reset();
}

void Board::Reset() {
    tiles.clear();
    tiles.resize(height);
    objects.clear();
    objects.push_back(new Player());
    GenerateBoard();
}

void Board::GenerateBoard() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> rand(1,5);

    for(int row = 0; row < height; row++) {
        if(tiles[row].capacity() < width) tiles[row].resize(width);

        for(int col = 0; col < width; col++) {
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
