
#include "Game/GameManager.h"

int main()
{
    GameManager* gameManager = new GameManager;

    gameManager->GameLoop();

    delete gameManager;
}
