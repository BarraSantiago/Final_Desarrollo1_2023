#include "GameManager.h"

GameManager::GameManager()
{
    InitWindow(1080, 720, "8Bit Battle Simulator");
    
    gameplayManager = new GameplayManager;
    menuManager = new MenuManager;
}

GameManager::~GameManager()
{
    delete menuManager;
    delete gameplayManager;
    CloseWindow();
}

bool GameManager::InGame() const
{
    return inGame;
}

void GameManager::GameLoop()
{
    while (!WindowShouldClose() && !menuManager->ExitGame())
    {
        if(!menuManager->InitGame())
        {
            menuManager->MenuLoop();
        }
        else
        {
            gameplayManager->GameLoop();
        }
    }
}
