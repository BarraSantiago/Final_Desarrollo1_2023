#include "GameManager.h"

#include <cmath>

GameManager::GameManager(): mouseSelection()
{
}

GameManager::~GameManager()
= default;

void GameManager::GameController()
{
    while (!WindowShouldClose())
    {
        Draw();
        Update();
    }
}

void GameManager::Update()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        boxStart = GetMousePosition();
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        boxEnd = GetMousePosition();
        mouseSelection.x = fmin(boxStart.x, boxEnd.x);
        mouseSelection.y = fmin(boxStart.y, boxEnd.y);
        mouseSelection.width = fabs(boxEnd.x - boxStart.x);
        mouseSelection.height = fabs(boxEnd.y - boxStart.y);
    }
}

void GameManager::Draw()
{
    BeginDrawing();
    //ClearBackground(WHITE);
    DrawRectangleRec(mouseSelection, RED);
    EndDrawing();
}
