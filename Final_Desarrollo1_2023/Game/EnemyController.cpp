#include "EnemyController.h"

#include <raymath.h>

#include "../Entity/Units/Archer.h"
#include "../Entity/Units/Cavalry.h"
#include "../Entity/Units/Soldier.h"

using namespace Entity;

namespace AIManager
{
    EnemyController::EnemyController(std::vector<Unit*> playerUnits)
    {
        this->playerUnits = playerUnits;
        enemyUnits.push_back(new Soldier{{500, 500}, enemy});
    }

    EnemyController::~EnemyController()
    {
    }

    void EnemyController::Update()
    {
        for (Unit* enemyUnit : enemyUnits)
        {
            Vector2 enemyPos = {enemyUnit->GetBody().x, enemyUnit->GetBody().y};
            enemyUnit->SetTarget(playerUnits[0]);
            enemyUnit->SetDestination({playerUnits[0]->GetBody().x, playerUnits[0]->GetBody().y});

            for (Unit* playerUnit : playerUnits)
            {
                Vector2 targetPos = {enemyUnit->GetTarget()->GetBody().x, enemyUnit->GetTarget()->GetBody().y};
                Vector2 playerPos = {playerUnit->GetBody().x, playerUnit->GetBody().y};

                if (Vector2Distance(playerPos, enemyPos) < Vector2Distance(targetPos, enemyPos))
                {
                    enemyUnit->SetTarget(playerUnit);
                    enemyUnit->SetDestination({playerUnit->GetBody().x, playerUnit->GetBody().y});
                }
            }
            enemyUnit->Move();
            enemyUnit->Attack();
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
}
