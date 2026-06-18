#include "Renderer.h"

#include <wx/brush.h>

#include "../Constants.h"
#include "AnimatedSprite.h"

// wczytywanie sprite'ów z plików
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

// zwracanie konkretnego sprite'a po nazwie
Sprite* Renderer::GetSprite(std::string name) {
    auto sprite = sprites.find(name);
    return sprite != sprites.end() ? sprite->second : nullptr;
}

// obsługa wyświetlania obektów na ekranie co każdą klatkę
void Renderer::DrawFrame(wxGraphicsContext* ctx, wxSize canvasSize) {
    Transform t{};
    t.scale = fmin(static_cast<double>(canvasSize.GetWidth()) / (board.width * TILE_SIZE),
                   (canvasSize.GetHeight()) / (board.height * TILE_SIZE));
    t.offsetX = (canvasSize.GetWidth() - board.width * TILE_SIZE * t.scale) / 2.0f;
    t.offsetY = ((canvasSize.GetHeight()) - board.height * TILE_SIZE * t.scale) / 2.0f;

    ctx->SetBrush(wxBrush(wxColor(80, 60, 60), wxBRUSHSTYLE_SOLID));
    ctx->DrawRectangle(0, 0, canvasSize.GetWidth(), canvasSize.GetHeight());

    DrawBoard(ctx, t);
    DrawObjects(ctx, t);
}

// wyświetlanie obiektów
void Renderer::DrawObjects(wxGraphicsContext* ctx, Transform& t) {
    for(auto object : board.objects) {
        Sprite* sprite = GetSprite(object->spriteName);
        if(sprite == nullptr) {
            sprite = GetSprite("error");
        }

        sprite->Draw(ctx, object->position.x, object->position.y, object->size.x, object->size.y, t, object->ticks);
    }
}

// wyświetlenie ścian
void Renderer::DrawBoard(wxGraphicsContext* ctx, Transform& t) {
    for(int row = 0; row < board.height; row++) {
        for(int col = 0; col < board.width; col++) {
            Tile* tile = &board.tiles[row][col];
            Sprite* sprite = nullptr;
            switch(tile->type) {
                case TileType::Solid: sprite = GetSprite("wall_solid"); break;
                case TileType::Destructible: sprite = GetSprite("wall_destructible"); break;
            }

            if(sprite != nullptr) {
                sprite->Draw(ctx, col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE, t, 0);
            }
        }
    }
}

// ustawienie koloru gracza według poprzedniego wyboru
void Renderer::SetPlayerColor(wxColour color) {
    delete sprites.at("player");
    sprites.insert_or_assign("player", new AnimatedSprite("assets/textures/player.png", 16, 15, color));
}
