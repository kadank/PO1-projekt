//
// Created by kabus on 8.06.2026.
//

#include "Renderer.h"

#include <iostream>

#include "../Constants.h"

Renderer::Renderer(Board& board) : board(board) {
    sprites.insert({"error", Sprite("assets/textures/error.png")});
    sprites.insert({"player", Sprite("assets/textures/player.png", wxColor(74, 195, 255))});
    sprites.insert({"wall_solid", Sprite("assets/textures/wall_solid.png")});
    sprites.insert({"wall_destructible", Sprite("assets/textures/wall_destructible.png")});
}

void Renderer::SetBoard(Board& board) {
    this->board = board;
}

Sprite* Renderer::GetSprite(std::string name) {
    auto sprite = sprites.find(name);
    return sprite != sprites.end() ? &sprite->second : nullptr;
}

void Renderer::DrawFrame(wxGraphicsContext* ctx, wxSize canvasSize) {
    Transform t{};
    t.scale = fmin(static_cast<double>(canvasSize.GetWidth()) / (board.width * TILE_SIZE), (canvasSize.GetHeight()) / (board.height * TILE_SIZE));
    t.offsetX = (canvasSize.GetWidth() - board.width * TILE_SIZE * t.scale) / 2.0f;
    t.offsetY = ((canvasSize.GetHeight()) - board.height * TILE_SIZE * t.scale ) / 2.0f;

    ctx->SetBrush(*wxBLACK_BRUSH);
    ctx->DrawRectangle(0, 0, canvasSize.GetWidth(), canvasSize.GetHeight());

    DrawBoard(ctx, t);
    DrawObjects(ctx, t);
}

void Renderer::DrawObjects(wxGraphicsContext* ctx, Transform& t) {
    for(auto object: board.objects) {
        Sprite* sprite = GetSprite(object->spriteName);
        if(sprite == nullptr) {
            sprite = GetSprite("error");
        }
        sprite->Draw(ctx, object->position.x, object->position.y, object->size.x, object->size.y, t);
    }
}

void Renderer::DrawBoard(wxGraphicsContext* ctx, Transform& t) {
    for(int row = 0; row < board.height; row++) {
        for(int col = 0; col < board.width; col++) {
            Tile* tile = &board.tiles[row][col];
            Sprite* sprite = nullptr;
            switch(tile->type) {
                case TileType::Solid:
                    sprite = GetSprite("wall_solid");
                    break;
                case TileType::Destructible:
                    sprite = GetSprite("wall_destructible");
                    break;
            }

            if(sprite != nullptr) {
                sprite->Draw(ctx, col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE, t);
            }
        }
    }
}

void Renderer::SetPlayerColor(wxColour color) {
    sprites.insert_or_assign("player", Sprite("assets/textures/player.png", color));
}
