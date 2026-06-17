#ifndef PROJEKT_BOARD_H
#define PROJEKT_BOARD_H
#include <list>
#include <vector>

#include "objects/Tile.h"

class Board {
public:
    std::vector<std::vector<Tile>> tiles;
    std::vector<Object*> objects;

    std::function<void(int)> onScoreChanged;
    std::function<void(int)> onLivesChanged;
    std::function<void(int)> onTimeChanged;
    std::function<void(wxString, wxString, wxString, std::function<void()>, wxString, std::function<void()>)>
        showOverlay;
    std::function<void()> hideOverlay;
    std::function<void()> onMainMenu;
    int width, height;

    int score, timeLeftTicks, lives, oldScore;

    Board(int width, int height);

    void Reset();
    void Restart();
    void NextLvl();
    void Respawn();
    void Pause();
    void Unpause();
    int CheckLvl();
    bool CheckPause();
    TileType CheckCollisions(Object& object, std::vector<Object*>* collidesWith);
    TileType CheckCollisions(Object& object);
    bool CheckCollisionsSimple(Object& object);

private:
    int level = 1;
    bool is_paused = false;
    void GenerateBoard();
    void SpawnEnemies();
};

#endif // PROJEKT_BOARD_H
