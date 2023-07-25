#include "EnemyController.h"

#include <raymath.h>

#include "GameManager.h"
#include "../Entity/Units/Archer.h"
#include "../Entity/Units/Cavalry.h"
#include "../Entity/Units/Soldier.h"

using namespace Entity;

std::vector<Unit*> GameManager::units;

namespace AIManager
{
    bool CheckDistance(Unit* unit, Unit* unit2, float distance)
    {
        Vector2 unit1Pos = {unit->GetBody().x, unit->GetBody().y};
        Vector2 unit2Pos = {unit2->GetBody().x, unit2->GetBody().y};
        return Vector2Distance(unit1Pos, unit2Pos) < distance;
    }

    bool CheckDistance(Unit* unit, Vector2 destination, float distance)
    {
        Vector2 unit1Pos = {unit->GetBody().x, unit->GetBody().y};

        return Vector2Distance(unit1Pos, destination) < distance;
    }

    EnemyController::EnemyController()
    {
        GameManager::units.push_back(new Soldier{{500, 500}, enemy});
    }

    EnemyController::~EnemyController()
    = default;

    void EnemyController::Update()
    {
        for (Unit* unit : GameManager::units)
        {
            if (unit->GetTeam() != enemy || !unit->IsAlive()) continue;

            if (AreAnyUnitsAlive(player))
            {
                UnitTargeting(unit);
            }

            unit->Move();

            unit->Attack();
        }
    }


    void EnemyController::Draw()
    {
        for (Unit* unit : GameManager::units)
        {
            unit->DrawBody();
            unit->DrawHP();
        }
    }

    void EnemyController::SpawnArcher(Vector2 position)
    {
        GameManager::units.push_back(new Archer{position, enemy});
    }

    void EnemyController::SpawnCavalry(Vector2 position)
    {
        GameManager::units.push_back(new Cavalry{position, enemy});
    }

    void EnemyController::SpawnSoldier(Vector2 position)
    {
        GameManager::units.push_back(new Soldier{position, enemy});
    }

    void EnemyController::UnitTargeting(Unit* unit)
    {
        Vector2 enemyPos = {unit->GetBody().x, unit->GetBody().y};
        Unit* nearestPlayerUnit = nullptr;
        float nearestDistance = std::numeric_limits<float>::max();

        for (Unit* playerUnit : GameManager::units)
        {
            if (!playerUnit || !playerUnit->IsAlive() || playerUnit->GetTeam() != player) continue;

            Vector2 targetPos = {playerUnit->GetBody().x, playerUnit->GetBody().y};

            // Calculate the distance between the current unit and the playerUnit
            float distanceToPlayerUnit = Vector2Distance(targetPos, enemyPos);

            // Compare the distance with the nearest found so far
            if (distanceToPlayerUnit < nearestDistance)
            {
                nearestDistance = distanceToPlayerUnit;
                nearestPlayerUnit = playerUnit;
            }
        }

        // Set the nearest playerUnit as the target and destination for the unit
        if (nearestPlayerUnit)
        {
            unit->SetTarget(nearestPlayerUnit);
            unit->SetDestination({nearestPlayerUnit->GetBody().x, nearestPlayerUnit->GetBody().y});
        }
    }


    bool EnemyController::AreAnyUnitsAlive(Team team)
    {
        for (Unit* unit : GameManager::units)
        {
            if (unit->GetTeam() != team) continue;
            if (unit->IsAlive()) return true;
        }
        return false;
    }
}
