#include "GameManager.h"
#include <cmath>

#include "../Entity/Units/Soldier.h"
#include "TargetSystem.h"
#include "../Entity/Units/Archer.h"
#include "../Entity/Units/Cavalry.h"

using namespace Entity;

GameManager::GameManager(): mouseSelection(), boxStart(), boxEnd()
{
    for (int i = 0; i < 1; ++i)
    {
        units.push_back(new Soldier);
        units.push_back(new Archer{{300, 150}, player});
        units.push_back(new Cavalry({50, 300}, player));
    }
    enemyController = new AIManager::EnemyController{units};
    for (Unit* unit : units)
    {
        unit->SetTarget(enemyController->GetEnemies()[0]);
    }

    enemyController->SpawnCavalry({600, 600});
    enemyController->SpawnCavalry({700, 600});
}

GameManager::~GameManager()
= default;

void GameManager::GameController()
{
    while (!WindowShouldClose())
    {
        Update();
        Draw();
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

    for (Unit* unit : units)
    {
        unit->SetSelected(CheckCollisionRecs(unit->GetBody(), mouseSelection));

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            Vector2 mouseTarget = GetMousePosition();
            if (unit->IsSelected())
            {
                unit->SetDestination(mouseTarget);
                if (!enemyController->GetEnemies().empty())
                    unit->SetTarget(targeting::GetTarget(mouseTarget, enemyController->GetEnemies()));
            }
        }
        unit->Attack();
        unit->Move();
    }
    for (Objects::Projectile* projectile : Archer::GetProjectiles())
    {
        projectile->Move();
    }
    units.erase(std::remove_if(units.begin(), units.end(), [](Unit* elem)
    {
        return !elem->IsAlive();
    }), units.end());

    enemyController->Update();
}

void GameManager::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    enemyController->Draw();
    for (Unit* unit : units)
    {
        unit->DrawBody();
        unit->DrawHP();
    }
    for (Objects::Projectile* projectile : Archer::GetProjectiles())
    {
        projectile->DrawBody();
    }
    DrawRectangleLinesEx(mouseSelection, 4, RED);
    EndDrawing();
}
