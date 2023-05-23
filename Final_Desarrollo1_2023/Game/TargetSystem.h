#pragma once
#include <raylib.h>
#include <vector>

#include "../entity/Unit.h"

Unit* GetTarget(Vector2 position, std::vector<Unit*> possibleTargets);
