#pragma once
#include <raylib.h>

class GameManager
{
public:
    GameManager();
    ~GameManager();
    void GameController();
    void Update();
    void Draw();
private:
    Rectangle mouseSelection;
    Vector2 boxStart;
    Vector2 boxEnd;
};
