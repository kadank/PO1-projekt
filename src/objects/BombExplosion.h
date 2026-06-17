#ifndef PROJEKT_BOMBEXPLOSION_H
#define PROJEKT_BOMBEXPLOSION_H
#include "Object.h"

class BombExplosion : public Object {
private:
    int ticks = 0;

public:
    BombExplosion(Board& board, Vector position);
    void Tick(std::set<char> pressedKeys) override;
};

#endif // PROJEKT_BOMBEXPLOSION_H
