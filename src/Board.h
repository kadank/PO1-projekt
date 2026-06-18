#ifndef PROJEKT_BOARD_H
#define PROJEKT_BOARD_H
#include "objects/Object.h"
#include <random>
#include <vector>

#include "objects/Tile.h"

enum class DeathType {
    Timeout,
    Enemy,
    Explosion,
    Final
};

class Board {
public:
    std::vector<std::vector<Tile>> tiles;
    std::vector<Object*> objects;

    std::function<void()> updateHud;
    std::function<void(wxString, wxString, wxString, std::function<void()>, wxString, std::function<void()>)>
        showOverlay;
    std::function<void()> hideOverlay;
    std::function<void()> onMainMenu;
    int width, height;

    int score, timeLeftTicks, lives, oldScore, level = 1;

    Board(int width, int height);

    void Reset();
    void Restart();
    void NextLvl();
    void Respawn();
    void SetPause(bool state);
    void KillPlayer(DeathType type);
    bool IsPaused();
    TileType CheckCollisions(Object& object, std::vector<Object*>* collidesWith);
    TileType CheckCollisions(Object& object);
    bool CheckCollisionsSimple(Object& object);

private:
    static std::mt19937 rng;
    bool isPaused = false;
    void GenerateBoard();
    void SpawnEnemies();
};

#endif // PROJEKT_BOARD_H
