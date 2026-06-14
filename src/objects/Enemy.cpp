//
// Created by kadank on 6/14/26.
//

#include "Enemy.h"

#include <random>

#include "../components/BombermanGame.h"
#include "../Constants.h"

Enemy::Enemy(Board& board, Vector position) : Object(position, Vector(TILE_SIZE, TILE_SIZE), "error", board) {
    DetermineDirection();
}

void Enemy::DetermineDirection(){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> rand(1,2);
    if (rand(rng)==1) {
        rotation = true;
    }else {
        rotation = false;
    }
    if (rand(rng)==1) {
        direction = true;
    }else {
        direction = false;
    }

    /*if (rotation) {
        int old = position.y;
        if (direction) {
            position.y +=1;
        }else {
            position.y -=1;
        }
        if(board.CheckCollisionsSimple(*this)) {
            direction = !direction;
        }
        position.y = old;
        if (direction) {
            position.y +=1;
        }else {
            position.y -=1;
        }
        if(board.CheckCollisions(*this)==TileType::Solid) {
            rotation = !rotation;
        }
        position.y = old;
    }else {
        int old = position.x;
        if (direction) {
            position.x +=1;
        }else {
            position.x -=1;
        }
        if(board.CheckCollisionsSimple(*this)) {
            direction = !direction;
        }
        position.x = old;
        if (direction) {
            position.x +=1;
        }else {
            position.x -=1;
        }
        if(board.CheckCollisions(*this)==TileType::Solid) {
            rotation = !rotation;
        }
        position.x = old;
    }*/



}

void Enemy::Tick(std::set<char> pressedKeys) {
        std::random_device dev;
        std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> rand(1,500);
    if (rand(rng)==1) direction = !direction;
    if (rotation) {
        int old = position.y;
        if (direction) {
            position.y +=1;
        }else
            position.y -=1;
        if(board.CheckCollisionsSimple(*this)) {
            position.y = old;
            std::uniform_int_distribution<std::mt19937::result_type> rand(1,3);
            switch (rand(rng)) {
                case 1:
                    direction = !direction;
                    break;
                case 2:
                    rotation = !rotation;
                    break;
                case 3:
                    rotation = !rotation;
                    direction = !direction;
                    break;
            }
        }

        old = position.x;
        position.x += 1;
        if(!board.CheckCollisionsSimple(*this)) {
            std::uniform_int_distribution<std::mt19937::result_type> rand(1,6);
            if (rand(rng)==1) rotation = !rotation;
        } else {
            position.x = old;
            position.x -= 1;
            if(!board.CheckCollisionsSimple(*this)) {
                std::uniform_int_distribution<std::mt19937::result_type> rand(1,6);
                if (rand(rng)==1) rotation = !rotation;
            }
        }
        position.x = old;



    }else {
        int old = position.x;

        if (direction) {
            position.x +=1;
        }else
            position.x -=1;
        if(board.CheckCollisionsSimple(*this)) {
            position.x = old;
            std::uniform_int_distribution<std::mt19937::result_type> rand(1,3);
            switch (rand(rng)) {
                case 1:
                    direction = !direction;
                    break;
                case 2:
                    rotation = !rotation;
                    break;
                case 3:
                    rotation = !rotation;
                    direction = !direction;
                    break;
            }
        }
        old = position.y;
        position.y += 1;
        if(!board.CheckCollisionsSimple(*this)) {
            std::uniform_int_distribution<std::mt19937::result_type> rand(1,6);
            if (rand(rng)==1) rotation = !rotation;
        } else {
            position.y = old;
            position.y -= 1;
            if(!board.CheckCollisionsSimple(*this)) {
                std::uniform_int_distribution<std::mt19937::result_type> rand(1,6);
                if (rand(rng)==1) rotation = !rotation;
            }
        }
        position.y = old;
    }
}