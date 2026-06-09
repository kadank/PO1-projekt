//
// Created by kabus on 27.04.2026.
//

#include "Board.h"

#include <iostream>
#include <random>
#include <list>

#include "Constants.h"
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
    objects.push_back(new Player(*this));
    GenerateBoard();
}

void Board::GenerateBoard() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> rand(1,5);

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

bool Board::CheckCollisions(Object &object, std::list<Object*>* collidesWith) {
    bool out = false;

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
                    out = true;
                    break;
                }
            }
        }
    }

    return out;
}

bool Board::CheckCollisions(Object &object) {
    return CheckCollisions(object, new std::list<Object*>());
}
