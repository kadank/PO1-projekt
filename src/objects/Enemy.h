#ifndef PROJEKT_ENEMY_H
#define PROJEKT_ENEMY_H
#include "Object.h"
#include <random>

class Enemy : public Object {
public:
    Enemy(Board& board, Vector position);

private:
    static std::mt19937 rng;
    bool rotation;
    bool direction;
    void DetermineDirection();
    void Tick(std::set<char> pressedKeys) override;
};

#endif // PROJEKT_ENEMY_H
