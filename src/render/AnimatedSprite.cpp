//
// Created by kabus on 15.06.2026.
//

#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(std::string texture_path, int frameWidth, int frameDuration) : Sprite(texture_path) {
    this->frameDuration = frameDuration;
    for(int x = 0; x < bitmap.GetWidth(); x += frameWidth) {
        frames.push_back(bitmap.GetSubBitmap(wxRect(x, 0, frameWidth, bitmap.GetHeight())));
    }
}

AnimatedSprite::AnimatedSprite(std::string texture_path, int frameWidth, int frameDuration, wxColour accent) : Sprite(texture_path, accent) {
    this->frameDuration = frameDuration;
    for(int x = 0; x < bitmap.GetWidth(); x += frameWidth) {
        frames.push_back(bitmap.GetSubBitmap(wxRect(x, 0, frameWidth, bitmap.GetHeight())));
    }
}

void AnimatedSprite::Draw(wxGraphicsContext *ctx, double x, double y, double w, double h, Transform t) {
    DrawFrame(ctx, x, y, w, h, t, 0);
}

void AnimatedSprite::DrawFrame(wxGraphicsContext *ctx, double x, double y, double w, double h, Transform t, int frameIndex) {
    if (frames.empty()) return;
    
    int safeFrame = frameIndex % frames.size();
    wxImage img = frames[safeFrame].ConvertToImage();

    img = img.Scale(
        ceil(w * t.scale),
        ceil(h * t.scale),
        wxIMAGE_QUALITY_NEAREST
    );

    wxBitmap scaled(img);
    ctx->DrawBitmap(scaled, X(x), Y(y), scaled.GetWidth(), scaled.GetHeight());
}
