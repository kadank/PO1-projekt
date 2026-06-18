#ifndef PROJEKT_RENDERER_H
#define PROJEKT_RENDERER_H

#include <map>
#include <string>

#include "../Board.h"
#include "Sprite.h"

class Renderer {
    std::map<std::string, Sprite*> sprites;
    Board& board;
    int frames = 0;

    Sprite* GetSprite(std::string name);
    void DrawObjects(wxGraphicsContext* ctx, Transform& t);
    void DrawBoard(wxGraphicsContext* ctx, Transform& t);

public:
    Renderer(Board& board);
    void SetPlayerColor(wxColor color);
    void SetBoard(Board& board);
    void DrawFrame(wxGraphicsContext* ctx, wxSize canvasSize);
};

#endif // PROJEKT_RENDERER_H
