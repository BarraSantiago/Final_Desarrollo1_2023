#include "TargetSystem.h"

#include <raylib.h>
#include <cmath>

#include "GameManager.h"
#include "../Entity/Unit.h"
using namespace Entity;

namespace targeting
{
    float CalculateDistance(const Vector2& point1, const Vector2& point2) {
        float dx = point2.x - point1.x;
        float dy = point2.y - point1.y;
        return std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
    }
    Unit* GetTarget(Vector2 position, std::vector<Unit*> units)
    {
        if(units.empty()) return nullptr;
        
        Unit* newTarget = units[0];
        
        float nearestDistance = CalculateDistance({newTarget->body.x, newTarget->body.y}, position);

        for (size_t i = 1; i < units.size(); ++i) {
            float distance = CalculateDistance({units[i]->body.x, units[i]->body.y}, position);
            if (distance < nearestDistance) {
                nearestDistance = distance;
                newTarget = units[i];
            }
        }
        return newTarget;
    }
}
