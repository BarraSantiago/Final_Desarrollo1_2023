#include "EnemyController.h"

#include <raymath.h>

#include "../Entity/Units/Archer.h"
#include "../Entity/Units/Cavalry.h"
#include "../Entity/Units/Soldier.h"

using namespace Entity;

namespace AIManager
{
    bool CheckDistance(Unit* unit, Unit* unit2, float distance)
    {
        Vector2 unit1Pos = {unit->GetBody().x, unit->GetBody().y};
        Vector2 unit2Pos = {unit2->GetBody().x, unit2->GetBody().y};
        return Vector2Distance(unit1Pos, unit2Pos) < distance;
    }

    EnemyController::EnemyController(std::vector<Unit*> playerUnits)
    {
        this->playerUnits = playerUnits;
        enemyUnits.push_back(new Soldier{{500, 500}, enemy});
        for (Unit* enemy : enemyUnits)
        {
            enemy->SetTarget(playerUnits[0]);
        }
    }

    EnemyController::~EnemyController()
    {
    }

    void EnemyController::Update()
    {
        for (Unit* unit : enemyUnits)
        {
            UnitTargeting(unit);
            
            if (CheckDistance(unit, unit->GetTarget(), unit->GetRange()*5))
                unit->Move();
            unit->Attack();
        }
        enemyUnits.erase(std::remove_if(enemyUnits.begin(), enemyUnits.end(), [](Unit* elem)
        {
            return !elem->IsAlive();
        }), enemyUnits.end());
    }


    void EnemyController::Draw()
    {
        for (Unit* unit : enemyUnits)
        {
            unit->DrawBody();
            unit->DrawHP();
        }
    }

    std::vector<Unit*> EnemyController::GetEnemies()
    {
        return enemyUnits;
    }

    void EnemyController::SpawnArcher(Vector2 position)
    {
        enemyUnits.push_back(new Archer{position, enemy});
    }

    void EnemyController::SpawnCavalry(Vector2 position)
    {
        enemyUnits.push_back(new Cavalry{position, enemy});
    }

    void EnemyController::SpawnSoldier(Vector2 position)
    {
        enemyUnits.push_back(new Soldier{position, enemy});
    }

    void EnemyController::UnitTargeting(Unit* unit)
    {
        Vector2 enemyPos = {unit->GetBody().x, unit->GetBody().y};
        
        unit->SetDestination({playerUnits[0]->GetBody().x, playerUnits[0]->GetBody().y});

        for (Unit* playerUnit : playerUnits)
        {
            Vector2 targetPos = {playerUnit->GetTarget()->GetBody().x, playerUnit->GetTarget()->GetBody().y};

            if (!playerUnit->IsAlive()) continue;

            //Checks for the nearest target, compares the distance between the current target with the new target
            float distanceBetweenTargets = Vector2Distance(targetPos, enemyPos);

            if (CheckDistance(unit, playerUnit, distanceBetweenTargets))
            {
                unit->SetTarget(playerUnit);
                unit->SetDestination({playerUnit->GetBody().x, playerUnit->GetBody().y});
            }
        }
    }
}
