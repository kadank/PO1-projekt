#include "Enemy.h"

#include <random>

#include "../Constants.h"
#include "../components/BombermanGame.h"
#include "Bomb.h"
#include "Player.h"

std::mt19937 Enemy::rng{std::random_device{}()};

Enemy::Enemy(Board& board, Vector position) : Object(position, Vector(TILE_SIZE, TILE_SIZE), "enemy", board) {
    DetermineDirection();
}
// funkcja losująca kierunek w którym pójdzie przeciwnik
void Enemy::DetermineDirection() {
    std::uniform_int_distribution<std::mt19937::result_type> rand(1, 2);
    if(rand(rng) == 1) {
        rotation = true;
    } else {
        rotation = false;
    }
    if(rand(rng) == 1) {
        direction = true;
    } else {
        direction = false;
    }
}

void Enemy::Tick(std::set<char> pressedKeys) {
    std::uniform_int_distribution<std::mt19937::result_type> rand(1, 500);

    std::vector<Object*> collidesWith;
    board.CheckCollisionsCircle(*this, &collidesWith);
    // if collision with player
    if(std::any_of(collidesWith.begin(), collidesWith.end(),
                   [](Object* obj) { return dynamic_cast<Player*>(obj) != nullptr; })) {
        board.KillPlayer(DeathType::Enemy);
    }
    // kolizja z bombą
    auto collidesWithBomb = [&]() -> bool {
        std::vector<Object*> tmp;
        board.CheckCollisions(*this, &tmp);
        return std::any_of(tmp.begin(), tmp.end(), [](Object* obj) { return dynamic_cast<Bomb*>(obj) != nullptr; });
    };
    // czekanie na ruch
    if(stayStillTicks > 0) {
        stayStillTicks--;
        return;
    }

    int random = rand(rng);
    if(random == 1) direction = !direction;
    if(random % 200 == 1) stayStillTicks += random % 120;

    if(rotation) {
        int old = position.y;

        if(direction) {
            position.y += 1;
        } else {
            position.y -= 1;
        }
        // decyzja przeciwnika w przypadku kolizji
        // zmiana kierunku lub czekanie
        if(board.CheckCollisionsSimple(*this) || collidesWithBomb()) {
            position.y = old;
            switch(random % 4) {
                case 0: direction = !direction; break;
                case 1: rotation = !rotation; break;
                case 2:
                    rotation = !rotation;
                    direction = !direction;
                    break;
                case 3: stayStillTicks += random % 120; break;
            }
        }
        // sprawdzanie czy można skręcić w bok i losowo decyduje czy skręcić
        old = position.x;
        position.x += 1;
        if(!(board.CheckCollisionsSimple(*this) || collidesWithBomb())) {
            if(random % 6 == 1) rotation = !rotation;
        } else {
            position.x = old;
            position.x -= 1;
            if(!(board.CheckCollisionsSimple(*this) || collidesWithBomb())) {
                if(random % 6 == 1) rotation = !rotation;
            }
        }
        position.x = old;

    } else {
        int old = position.x;

        if(direction) {
            position.x += 1;
        } else {
            position.x -= 1;
        }
        // decyzja przeciwnika w przypadku kolizji
        // zmiana kierunku lub czekanie
        if(board.CheckCollisionsSimple(*this) || collidesWithBomb()) {
            position.x = old;
            switch(random % 4) {
                case 0: direction = !direction; break;
                case 1: rotation = !rotation; break;
                case 2:
                    rotation = !rotation;
                    direction = !direction;
                    break;
                case 3: stayStillTicks += random % 60; break;
            }
        }
        // sprawdzanie czy można skręcić w bok i losowo decyduje czy skręcić
        old = position.y;
        position.y += 1;
        if(!(board.CheckCollisionsSimple(*this) || collidesWithBomb())) {
            if(random % 6 == 1) rotation = !rotation;
        } else {
            position.y = old;
            position.y -= 1;
            if(!(board.CheckCollisionsSimple(*this) || collidesWithBomb())) {
                if(random % 6 == 1) rotation = !rotation;
            }
        }
        position.y = old;
    }
}
