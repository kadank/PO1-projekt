//
// Created by kabus on 27.04.2026.
//

#include "Object.h"

void Object::Tick(double delta) {

}

void Object::Render(wxGraphicsContext *gc) {
    gc->SetBrush(*wxRED_BRUSH);
    gc->DrawRectangle(position.x, position.y, size.x, size.y);
    gc->SetBrush(*wxBLUE_BRUSH);
    gc->DrawRectangle(position.x, position.y, size.x / 2.0, size.y / 2.0);
    gc->DrawRectangle(position.x + size.x / 2.0, position.y + size.y / 2.0, size.x / 2.0, size.y / 2.0);
}

Object::Object(Vector position, Vector size) : position(position), size(size) {}
