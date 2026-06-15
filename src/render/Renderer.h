//
// Created by kabus on 8.06.2026.
//

#ifndef PROJEKT_RENDERER_H
#define PROJEKT_RENDERER_H

#include <map>
#include <string>

#include "Sprite.h"
#include "../Board.h"

class Renderer {
    std::map<std::string, Sprite*> sprites;
    Board& board;

    Sprite* GetSprite(std::string name);
    void DrawObjects(wxGraphicsContext* ctx, Transform& t);
    void DrawBoard(wxGraphicsContext* ctx, Transform& t);

public:
    Renderer(Board& board);
    void SetPlayerColor(wxColor color);
    void SetBoard(Board& board);
    void DrawFrame(wxGraphicsContext* ctx, wxSize canvasSize);
};



#endif //PROJEKT_RENDERER_H
