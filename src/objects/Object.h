//
// Created by kabus on 27.04.2026.
//

#ifndef PROJEKT_OBJECT_H
#define PROJEKT_OBJECT_H
#include <wx/graphics.h>

#include "../utils/Vector.h"

class Object {
public:
    Vector position;
    Vector size;

    Object(Vector position, Vector size);

    virtual void Tick(double delta);
    virtual void Render(wxGraphicsContext* gc);
};

#endif //PROJEKT_OBJECT_H
