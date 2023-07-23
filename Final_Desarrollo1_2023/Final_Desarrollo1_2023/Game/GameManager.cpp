﻿#include "GameManager.h"
#include <cmath>
#include <iostream>

#include "../Entity/Units/Soldier.h"
#include "TargetSystem.h"
#include "../Entity/Units/Archer.h"
#include "../Entity/Units/Cavalry.h"

using namespace Entity;

GameManager::GameManager(): mouseSelection(), boxStart(), boxEnd(), actionPerformed(false)
{
    units.push_back(new Cavalry({50, 300}, player));

    enemyController = new AIManager::EnemyController{units};
    for (Unit* unit : units)
    {
        unit->SetTarget(enemyController->GetEnemies()[0]);
    }

    enemyController->SpawnCavalry({111, 111});
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
    actionPerformed = false;
    MouseManager();

    UnitsManager();
    if (!actionPerformed)SpawnManager(GetCharPressed());
    enemyController->Update();
    
    RemoveDeadUnits();
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
        units.push_back(new Soldier{GetMousePosition(), player});
        actionPerformed = true;
        break;
    case 'w':
    case 'W':
        units.push_back(new Cavalry{GetMousePosition(), player});
        actionPerformed = true;
        break;
    case 'e':
    case 'E':
        units.push_back(new Archer{GetMousePosition(), player});
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
        mouseSelection = {0,0,0,0};
    }
}

void GameManager::UnitsManager()
{
    for (Unit* unit : units)
    {
        SelectUnit(unit);
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            Vector2 mouseTarget = GetMousePosition();
            if (unit->IsSelected())
            {
                unit->SetDestination(mouseTarget);
                if (!enemyController->GetEnemies().empty())
                {
                    unit->SetTarget(targeting::GetTarget(mouseTarget, enemyController->GetEnemies()));
                }
            }
        }
        unit->Move();
        unit->Attack();
    }
    for (Objects::Projectile* projectile : Archer::GetProjectiles())
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
    for (Unit* unit : units)
    {
        if(unit->IsSelected()) unit->SetSelected(false);
    }
}


void GameManager::RemoveDeadUnits()
{
    units.erase(std::remove_if(units.begin(), units.end(), [](Unit* elem)
    {
        return !elem->IsAlive();
    }), units.end());
}
