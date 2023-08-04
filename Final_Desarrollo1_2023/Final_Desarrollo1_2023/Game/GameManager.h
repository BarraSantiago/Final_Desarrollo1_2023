#pragma once
#include "../Gameplay/GameplayManager.h"
#include "../Menu/MenuManager.h"

class GameManager
{
public:
    GameManager();
    ~GameManager();
    void GameLoop();

    bool InGame() const;
private:
    MenuManager* menuManager;
    GameplayManager* gameplayManager;

    bool inGame=true;
};
