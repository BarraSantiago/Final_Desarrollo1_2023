#include "GameManager.h"
#include <cmath>

#include "../Entity/Soldier.h"

GameManager::GameManager(): mouseSelection(), boxStart(), boxEnd()
{
    for (int i = 0; i < 1; ++i)
    {
        untis.push_back(new Soldier);
    }
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

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        boxEnd = GetMousePosition();
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        boxEnd = GetMousePosition();
    }

    mouseSelection.x = fmin(boxStart.x, boxEnd.x);
    mouseSelection.y = fmin(boxStart.y, boxEnd.y);
    mouseSelection.width = fabs(boxEnd.x - boxStart.x);
    mouseSelection.height = fabs(boxEnd.y - boxStart.y);

    for (Unit* unit : untis)
    {
        unit->SetSelected(CheckCollisionRecs(unit->GetBody(), mouseSelection));

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            if (unit->IsSelected()) unit->SetDestination(GetMousePosition());
        }

        unit->Move();
    }
}

void GameManager::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);
    for (Unit* unit : untis)
    {
        unit->DrawBody();
        unit->DrawHP();
    }
    DrawRectangleLinesEx(mouseSelection, 4, RED);
    EndDrawing();
}
