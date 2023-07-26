#pragma once
#include "Unit.h"

namespace Check
{
    bool InRange(Rectangle body, Rectangle targetBody, float range);
    bool AABBCollision(Entity::DefaultEntity* a, Entity::DefaultEntity* b);

}
