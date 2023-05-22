#include "raylib.h"
#include "Game/GameManager.h"
int main()
{
    InitWindow(1080, 720, "se");
    
    GameManager* game_manager = new GameManager;
    game_manager->GameController();
    delete game_manager;
    CloseWindow();
}