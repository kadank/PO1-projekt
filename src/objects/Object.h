#ifndef PROJEKT_OBJECT_H
#define PROJEKT_OBJECT_H
#include <set>
#include <wx/graphics.h>

#include "../utils/Vector.h"

class Board;

struct AnimationState {
    int currentFrame = 0;
    int frameCounter = 0;
    int frameDuration = 0;
};

class Object {
public:
    Vector position;
    Vector size;
    std::string spriteName;
    Board& board;
    bool flagDelete = false;
    AnimationState animationState;

    Object(Vector position, Vector size, std::string spriteName, Board& board);

    virtual void Tick(std::set<char> pressedKeys);
};

#endif // PROJEKT_OBJECT_H
