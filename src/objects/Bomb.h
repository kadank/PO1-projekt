#ifndef PROJEKT_BOMB_H
#define PROJEKT_BOMB_H
#include "Object.h"
#include "../Constants.h"


class Bomb : public Object {
private:
    int ticks = 0;

public:
    Bomb(Board& board, Vector position);

    void Tick(std::set<char> pressedKeys) override;
};



#endif //PROJEKT_BOMB_H
