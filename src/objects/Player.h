#ifndef PROJEKT_PLAYER_H
#define PROJEKT_PLAYER_H
#include "Object.h"

class Player: public Object {
    void HandleMovement(std::set<char> pressedKeys, char key, double& moveAxis, double& offsetAxis, int moveDir);

public:
    Player(Board& board);

    void Tick(std::set<char> pressedKeys) override;
};

#endif //PROJEKT_PLAYER_H
