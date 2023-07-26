#include "GameManager.h"
#include <cmath>
#include <iostream>

#include "../Entity/Units/Soldier.h"
#include "TargetSystem.h"
#include "../Entity/Units/Archer.h"
#include "../Entity/Units/Cavalry.h"

using namespace Entity;

std::vector<Unit*> GameManager::playerUnits;
std::vector<Unit*> GameManager::enemyUnits;

GameManager::GameManager(): mouseSelection(), boxStart(), boxEnd(), actionPerformed(false)
{
    playerUnits.push_back(new Cavalry({50, 300}, player));

    enemyController = new AIManager::EnemyController;

    enemyController->SpawnCavalry({111, 111});
}

GameManager::~GameManager()
{
    delete enemyController;
    for (Unit* unit : playerUnits)
    {
        delete unit;
    }
    for (Unit* unit : enemyUnits)
    {
        delete unit;
    }
}

void GameManager::GameFlow()
{
    while (!WindowShouldClose())
    {
        Update();
        Draw();
    }
}

void GameManager::Update()
{
    actionPerformed = false;
    MouseManager();

    UnitsManager();
    if (!actionPerformed)SpawnManager(GetCharPressed());
    enemyController->Update();

    RemoveDeadUnits(playerUnits);
    RemoveDeadUnits(enemyUnits);
    RemoveDeadProjectiles(Archer::projectiles);
}

void GameManager::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    enemyController->Draw();

    for (Unit* unit : playerUnits)
    {
        unit->DrawBody();
        unit->DrawHP();
    }

    for (Objects::Projectile* projectile : Archer::projectiles)
    {
        projectile->DrawBody();
    }

    DrawRectangleLinesEx(mouseSelection, 4, RED);
    EndDrawing();
}

void GameManager::SpawnManager(char input)
{
    //TODO REMOVE MAGIC LETTERS
    switch (input)
    {
    case 'q':
    case 'Q':
        playerUnits.push_back(new Soldier{GetMousePosition(), player});
        actionPerformed = true;
        break;
    case 'w':
    case 'W':
        playerUnits.push_back(new Cavalry{GetMousePosition(), player});
        actionPerformed = true;
        break;
    case 'e':
    case 'E':
        playerUnits.push_back(new Archer{GetMousePosition(), player});
        actionPerformed = true;
        break;
    default:
        break;
    }
}

void GameManager::MouseManager()
{
    const int mainMouseButton = MOUSE_BUTTON_LEFT;
    if (IsMouseButtonPressed(mainMouseButton))
    {
        boxStart = GetMousePosition();
        DeselectUnits();
    }

    if (IsMouseButtonDown(mainMouseButton))
    {
        boxEnd = GetMousePosition();
        mouseSelection.x = fmin(boxStart.x, boxEnd.x);
        mouseSelection.y = fmin(boxStart.y, boxEnd.y);
        mouseSelection.width = fabs(boxEnd.x - boxStart.x);
        mouseSelection.height = fabs(boxEnd.y - boxStart.y);
    }
    else
    {
        mouseSelection = {0, 0, 0, 0};
    }
}

void GameManager::UnitsManager()
{
    for (Unit* unit : playerUnits)
    {
        SelectUnit(unit);

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            if(!unit->IsSelected()) continue;
            
            Vector2 mouseTarget = GetMousePosition();

            unit->SetDestination(mouseTarget);

            if (!enemyUnits.empty())
            {
                unit->SetTarget(targeting::GetTarget(mouseTarget, enemyUnits));
            }
        }

        unit->Move();
        unit->Attack();
    }

    for (Objects::Projectile* projectile : Archer::projectiles)
    {
        projectile->Move();
    }
}


void GameManager::SelectUnit(Unit* unit) const
{
    if (CheckCollisionRecs(unit->GetBody(), mouseSelection))
    {
        unit->SetSelected(true);
    }
}

void GameManager::DeselectUnits()
{
    for (Unit* unit : playerUnits)
    {
        if (unit->IsSelected()) unit->SetSelected(false);
    }
}


void GameManager::RemoveDeadUnits(std::vector<Unit*>& units)
{
    units.erase(std::remove_if(units.begin(), units.end(),
                               [](Unit* unit)
                               {
                                   return !unit->IsAlive();
                               }), units.end());
}

void GameManager::RemoveDeadProjectiles(std::vector<Objects::Projectile*>& projectile)
{
    projectile.erase(std::remove_if(projectile.begin(), projectile.end(),
                                    [](Objects::Projectile* projectile)
                                    {
                                        return !projectile->IsAlive();
                                    }), projectile.end());
}
