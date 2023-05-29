#pragma once
#include "Unit.h"

namespace Check
{
    bool InRange(Rectangle body, Rectangle targetBody, float range);
    bool SameTeam(Entity::Team team, Entity::Team targetTeam);
    bool Collision(Rectangle body1, Rectangle body2);
}
