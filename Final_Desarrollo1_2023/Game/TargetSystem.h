#pragma once
#include <raylib.h>
#include <vector>

#include "../entity/Unit.h"

namespace targeting
{
    Entity::Unit* GetTarget(Vector2 position, std::vector<Entity::Unit*> possibleTargets);
}
