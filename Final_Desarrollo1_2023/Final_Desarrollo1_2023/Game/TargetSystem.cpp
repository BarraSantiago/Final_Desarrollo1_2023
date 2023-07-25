#include "TargetSystem.h"

#include <raylib.h>
#include <raymath.h>

#include "GameManager.h"
#include "../Entity/Unit.h"
using namespace Entity;

namespace targeting
{
    Unit* GetTarget(Vector2 position, Team teamTargeted)
    {
        Unit* newTarget = GameManager::units[0];

        for (Unit* unit : GameManager::units)
        {
            if (unit->GetTeam() == teamTargeted)
            {
                newTarget = unit;
                break;
            }
        }
        
        for (Unit* target : GameManager::units)
        {
            if (target->GetTeam() != teamTargeted) continue;
            
            Vector2 targetPos = {newTarget->GetBody().x, newTarget->GetBody().y};
            Vector2 playerPos = {target->GetBody().x, target->GetBody().y};

            if (Vector2Distance(playerPos, position) < Vector2Distance(targetPos, position))
            {
                newTarget = target;
            }
        }
        return newTarget;
    }
}
