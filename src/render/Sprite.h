#ifndef PROJEKT_SPRITE_H
#define PROJEKT_SPRITE_H
#include <wx/bitmap.h>
#include <wx/graphics.h>

#include "Transform.h"

class Sprite {
protected:
    wxBitmap bitmap;

public:
    Sprite(std::string texture_path);
    Sprite(std::string texture_path, wxColor accent);
    virtual void Draw(wxGraphicsContext* ctx, double x, double y, double w, double h, Transform t, int frames);
};

#endif // PROJEKT_SPRITE_H
