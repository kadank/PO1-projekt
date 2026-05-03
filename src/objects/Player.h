//
// Created by kabus on 29.04.2026.
//

#ifndef PROJEKT_PLAYER_H
#define PROJEKT_PLAYER_H
#include "Object.h"

class Player: public Object {
public:
    Player();

    void Render(wxGraphicsContext *gc) override;
};

#endif //PROJEKT_PLAYER_H
