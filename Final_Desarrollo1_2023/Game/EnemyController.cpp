#include "EnemyController.h"

#include <raymath.h>

#include "../Entity/Soldier.h"

EnemyController::EnemyController(std::vector<Unit*> playerUnits)
{
    this->playerUnits = playerUnits;
    enemyUnits.push_back(new Soldier{100, 15, 20, 30, {500, 500, 50, 75}, enemy});
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

        for (Unit* playerUnit : playerUnits)
        {
            Vector2 targetPos = {enemyUnit->GetTarget()->GetBody().x, enemyUnit->GetTarget()->GetBody().y};
            Vector2 playerPos = {playerUnit->GetBody().x, playerUnit->GetBody().y};

            if (Vector2Distance(playerPos, enemyPos) < Vector2Distance(targetPos, enemyPos))
            {
                enemyUnit->SetTarget(playerUnit);
            }
        }
        enemyUnit->SetDestination({enemyUnit->GetTarget()->GetBody().x, enemyUnit->GetTarget()->GetBody().y});
    }
}

void EnemyController::Draw()
{
    for (Unit* unit : enemyUnits)
    {
        unit->DrawBody();
        unit->DrawHP();
    }
}