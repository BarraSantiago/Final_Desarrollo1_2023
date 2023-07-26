#include "Checks.h"

#include <raylib.h>
#include <raymath.h>

#include "Unit.h"

namespace Check
{
    bool InRange(Rectangle body, Rectangle targetBody, float range)
    {
        float unitX = body.x + body.width / 2;
        float unitY = body.y + body.height / 2;

        float targetX = targetBody.x + targetBody.width / 2;
        float targetY = targetBody.y + targetBody.height / 2;

        //if target isn't in range, no calculation is made
        return Vector2Distance({unitX, unitY}, {targetX, targetY}) > range;
    }
}
