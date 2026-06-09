//
// Created by kabus on 27.04.2026.
//

#include "Object.h"

void Object::Tick(std::set<char> pressedKeys) {

}

Object::Object(Vector position, Vector size, std::string spriteName, Board& board) : position(position), size(size), spriteName(spriteName), board(board) {}
