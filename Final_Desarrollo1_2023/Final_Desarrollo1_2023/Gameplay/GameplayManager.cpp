#include "GameplayManager.h"
#include <cmath>
#include <iostream>

#include "TargetSystem.h"
#include "../Entity/Units/Soldier.h"
#include "../Entity/Units/Archer.h"
#include "../Entity/Units/Cavalry.h"

using namespace Entity;

std::vector<Unit*> GameplayManager::playerUnits;
std::vector<Unit*> GameplayManager::enemyUnits;

GameplayManager::GameplayManager(): mouseSelection(), boxStart(), boxEnd(), actionPerformed(false)
{
    background = LoadTexture("../res/background.png");
    solTexture = LoadTexture("../res/blue-knight.png");
    arcTexture = LoadTexture("../res/blue-archer.png");
    cavTexture = LoadTexture("../res/blue-cavalry.png");
    Objects::Projectile::redTexture = LoadTexture("../res/red-arrow.png");
    Objects::Projectile::blueTexture = LoadTexture("../res/blue-arrow.png");
    enemyController = new AIManager::EnemyController;
}

GameplayManager::~GameplayManager()
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

    UnloadTexture(background);
    UnloadTexture(solTexture);
    UnloadTexture(arcTexture);
    UnloadTexture(cavTexture);
    UnloadTexture(Objects::Projectile::redTexture);
    UnloadTexture(Objects::Projectile::blueTexture);
}

void GameplayManager::GameLoop()
{
    Update();
    Draw();
}

void GameplayManager::Update()
{
    actionPerformed = false;
    MouseManager();

    UnitsManager();
    if (!actionPerformed)SpawnManager(GetCharPressed());

    AIManager::EnemyController::Update();

    RemoveDeadUnits(playerUnits);
    RemoveDeadUnits(enemyUnits);
    RemoveDeadProjectiles(Archer::projectiles);
}

void GameplayManager::Draw() const
{
    BeginDrawing();
    ClearBackground(BLACK);

    DrawTextureEx(background, {0, 0}, 0, 1.f, WHITE);

    AIManager::EnemyController::Draw();

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

void GameplayManager::SpawnManager(char input)
{
    switch (toupper(input))
    {
    case '1':
        enemyController->SpawnSoldier(GetMousePosition());
        break;
    case '2':
        enemyController->SpawnCavalry(GetMousePosition());
        break;
    case '3':
        enemyController->SpawnArcher(GetMousePosition());
        break;
    case 'Q':
        playerUnits.push_back(new Soldier{GetMousePosition(), player, solTexture});
        actionPerformed = true;
        break;
    case 'W':
        playerUnits.push_back(new Cavalry{GetMousePosition(), player, cavTexture});
        actionPerformed = true;
        break;
    case 'E':
        playerUnits.push_back(new Archer{GetMousePosition(), player, arcTexture});
        actionPerformed = true;
        break;
    default:
        break;
    }
}

void GameplayManager::MouseManager()
{
    constexpr int mainMouseButton = MOUSE_BUTTON_LEFT;

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

void GameplayManager::UnitsManager() const
{
    for (Unit* unit : playerUnits)
    {
        SelectUnit(unit);

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            if (!unit->IsSelected()) continue;

            const Vector2 mouseTarget = GetMousePosition();

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


void GameplayManager::SelectUnit(Unit* unit) const
{
    if (CheckCollisionRecs(unit->GetBody(), mouseSelection))
    {
        unit->SetSelected(true);
    }
}

void GameplayManager::DeselectUnits()
{
    for (Unit* unit : playerUnits)
    {
        if (unit->IsSelected()) unit->SetSelected(false);
    }
}


void GameplayManager::RemoveDeadUnits(std::vector<Unit*>& units)
{
    units.erase(std::remove_if(units.begin(), units.end(),
                               [](Unit* unit)
                               {
                                   return !unit->IsAlive();
                               }), units.end());
}

void GameplayManager::RemoveDeadProjectiles(std::vector<Objects::Projectile*>& projectile)
{
    projectile.erase(std::remove_if(projectile.begin(), projectile.end(),
                                    [](Objects::Projectile* projectile)
                                    {
                                        return !projectile->IsAlive();
                                    }), projectile.end());
}
