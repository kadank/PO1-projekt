//
// Created by kabus on 8.06.2026.
//

#include "Renderer.h"

#include <iostream>

#include "AnimatedSprite.h"
#include "../Constants.h"

Renderer::Renderer(Board& board) : board(board) {
    sprites.insert({"error", new Sprite("assets/textures/error.png")});
    sprites.insert({"player", new AnimatedSprite("assets/textures/player.png", 16, 15, wxColor(74, 195, 255))});
    sprites.insert({"wall_solid", new Sprite("assets/textures/wall_solid.png")});
    sprites.insert({"wall_destructible", new Sprite("assets/textures/wall_destructible.png")});
    sprites.insert({"bomb", new AnimatedSprite("assets/textures/bomb.png", 16, 45)});
    sprites.insert({"explosion", new Sprite("assets/textures/explosion.png")});
    sprites.insert({"enemy", new AnimatedSprite("assets/textures/enemy.png", 16, 10)});
}

void Renderer::SetBoard(Board& board) {
    this->board = board;
}

Sprite* Renderer::GetSprite(std::string name) {
    auto sprite = sprites.find(name);
    return sprite != sprites.end() ? sprite->second : nullptr;
}

void Renderer::DrawFrame(wxGraphicsContext* ctx, wxSize canvasSize) {
    Transform t{};
    t.scale = fmin(static_cast<double>(canvasSize.GetWidth()) / (board.width * TILE_SIZE), (canvasSize.GetHeight()) / (board.height * TILE_SIZE));
    t.offsetX = (canvasSize.GetWidth() - board.width * TILE_SIZE * t.scale) / 2.0f;
    t.offsetY = ((canvasSize.GetHeight()) - board.height * TILE_SIZE * t.scale ) / 2.0f;

    ctx->SetBrush(*wxGREY_BRUSH);
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
        
        AnimatedSprite* animSprite = dynamic_cast<AnimatedSprite*>(sprite);
        if (animSprite != nullptr) {
            if (object->animationState.frameDuration == 0) {
                object->animationState.frameDuration = animSprite->GetFrameDuration();
            }
            object->animationState.frameCounter++;
            if (object->animationState.frameCounter >= object->animationState.frameDuration) {
                object->animationState.currentFrame = (object->animationState.currentFrame + 1) % animSprite->GetFrameCount();
                object->animationState.frameCounter = 0;
            }
            animSprite->DrawFrame(ctx, object->position.x, object->position.y, object->size.x, object->size.y, t, object->animationState.currentFrame);
        } else {
            sprite->Draw(ctx, object->position.x, object->position.y, object->size.x, object->size.y, t);
        }
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
    sprites.insert_or_assign("player", new AnimatedSprite("assets/textures/player.png", 16, 15, color));
}
