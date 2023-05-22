#include "raylib.h"
#include "Game/GameManager.h"

int main()
{
    InitWindow(1080, 1920, "se");

    SetTargetFPS(60);
    
    GameManager* game_manager = new GameManager;

    game_manager->GameController();
    delete game_manager;

    CloseWindow();
}
