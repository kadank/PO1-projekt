//
// Created by kabus on 27.04.2026.
//

#ifndef PROJEKT_OBJECT_H
#define PROJEKT_OBJECT_H
#include <set>
#include <wx/graphics.h>

#include "../render/Sprite.h"
#include "../utils/Vector.h"

class Board;

class Object {
public:
    Vector position;
    Vector size;
    std::string spriteName;
    Board& board;

    Object(Vector position, Vector size, std::string spriteName, Board& board);

    virtual void Tick(std::set<char> pressedKeys);
};

#endif //PROJEKT_OBJECT_H
