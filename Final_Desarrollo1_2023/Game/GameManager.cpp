#include "GameManager.h"
#include <cmath>

GameManager::GameManager(): mouseSelection(), boxStart(), boxEnd()
{
    basicUnit = new Unit;
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

    basicUnit->SetSelected(CheckCollisionRecs(basicUnit->GetBody(), mouseSelection));
    
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        if (basicUnit->IsSelected()) basicUnit->SetDestination(GetMousePosition());
    }

    basicUnit->Move();
    basicUnit->ModifyHealth(-5 * GetFrameTime());
}

void GameManager::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);
    basicUnit->DrawBody();
    basicUnit->DrawHP();
    DrawRectangleLinesEx(mouseSelection, 4, RED);
    EndDrawing();
}
