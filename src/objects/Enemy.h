//
// Created by kadank on 6/14/26.
//

#ifndef PROJEKT_ENEMY_H
#define PROJEKT_ENEMY_H
#include "Object.h"

class Enemy:public Object {
public:
    Enemy(Board& board, Vector position);

private:
    bool rotation;
    bool direction;
    void DetermineDirection();
    void Tick(std::set<char> pressedKeys) override;
};


#endif //PROJEKT_ENEMY_H
