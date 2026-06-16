#include "Enemy.h"

#include <random>

#include "Bomb.h"
#include "../components/BombermanGame.h"
#include "../Constants.h"

Enemy::Enemy(Board& board, Vector position) : Object(position, Vector(TILE_SIZE, TILE_SIZE), "enemy", board) {
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

}

void Enemy::Tick(std::set<char> pressedKeys) {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> rand(1,500);


    auto collidesWithBomb = [&]() -> bool {
        std::vector<Object*> tmp;
        board.CheckCollisions(*this, &tmp);
        return std::any_of(tmp.begin(), tmp.end(), [](Object* obj){ return dynamic_cast<Bomb*>(obj) != nullptr; });
    };

    int random = rand(rng);
    if (random==1) direction = !direction;

    if (rotation) {
        int old = position.y;
        if (direction) {
            position.y +=1;
        }else
            position.y -=1;
        if(board.CheckCollisionsSimple(*this) || collidesWithBomb()) {
            position.y = old;
            switch (random%3) {
                case 0:
                    direction = !direction;
                    break;
                case 1:
                    rotation = !rotation;
                    break;
                case 2:
                    rotation = !rotation;
                    direction = !direction;
                    break;
            }
        }

        old = position.x;
        position.x += 1;
        if(!(board.CheckCollisionsSimple(*this) || collidesWithBomb())) {
            if (random%6==1) rotation = !rotation;
        } else {
            position.x = old;
            position.x -= 1;
            if(!(board.CheckCollisionsSimple(*this) || collidesWithBomb())) {
                if (random%6==1) rotation = !rotation;
            }
        }
        position.x = old;



    }else {
        int old = position.x;

        if (direction) {
            position.x +=1;
        }else
            position.x -=1;
        if(board.CheckCollisionsSimple(*this)|| collidesWithBomb()) {
            position.x = old;
            switch (random%3) {
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
        if(!(board.CheckCollisionsSimple(*this)|| collidesWithBomb())) {
            if (random%6==1) rotation = !rotation;
        } else {
            position.y = old;
            position.y -= 1;
            if(!(board.CheckCollisionsSimple(*this)|| collidesWithBomb())) {
                if (random%6==1) rotation = !rotation;
            }
        }
        position.y = old;
    }
}
