#include "TargetSystem.h"

#include <raylib.h>
#include <raymath.h>

#include "../Entity/Unit.h"
using namespace Entity;

namespace targeting
{
    Unit* GetTarget(Vector2 position, std::vector<Unit*> possibleTargets)
    {
        Unit* newTarget = possibleTargets[0];
        for (Unit* target : possibleTargets)
        {
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
