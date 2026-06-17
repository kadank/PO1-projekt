#ifndef PROJEKT_ANIMATEDSPRITE_H
#define PROJEKT_ANIMATEDSPRITE_H
#include "Sprite.h"

class AnimatedSprite : public Sprite {
    std::vector<wxBitmap> frames;
    int frameDuration;

public:
    AnimatedSprite(std::string texture_path, int frameWidth, int frameDuration);
    AnimatedSprite(std::string texture_path, int frameWidth, int frameDuration, wxColor accent);
    void Draw(wxGraphicsContext* ctx, double x, double y, double w, double h, Transform t) override;
    void DrawFrame(wxGraphicsContext* ctx, double x, double y, double w, double h, Transform t, int frameIndex);
    int GetFrameCount() const {
        return frames.size();
    }
    int GetFrameDuration() const {
        return frameDuration;
    }
};

#endif // PROJEKT_ANIMATEDSPRITE_H
