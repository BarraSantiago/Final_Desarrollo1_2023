#include "Unit.h"

#include <cmath>
#include "raymath.h"

namespace Entity
{
    Unit::~Unit()
    = default;

    Unit::Unit(): hp(100), currentHP(100), attack(20), range(5), attackSpeed(1), attackCooldown(1), speed(50),
                  distanceX(0), distanceY(0), selected(false), alive(true), team(player),
                  target(nullptr), destination({200, 200})
    {
        body = {200, 200, 100, 100};
    }
    bool Vector2IsEqual(const Vector2& vec1, const Vector2& vec2, float tolerance = 0.01f) {
        return (std::fabs(vec1.x - vec2.x) <= tolerance) && (std::fabs(vec1.y - vec2.y) <= tolerance);
    }
    void Unit::Move()
    {
        Vector2 position = {body.x, body.y};
        if (!Vector2IsEqual(position, newDestination))
        {
            float distance = speed * GetFrameTime();
            Vector2 movementDelta = Vector2Scale(Vector2Normalize(destination), distance);
            position = Vector2Add({body.x, body.y}, movementDelta);
            body.x = position.x;
            body.y = position.y;
        }
    }

    void Unit::SetDestination(Vector2 newDestination)
    {
        this->newDestination = newDestination;
        destination = Vector2Subtract(newDestination, {body.x, body.y});
        distanceX = Vector2Distance({body.x, 0}, newDestination);
        distanceY = Vector2Distance({0, body.y}, newDestination);
    }

    void Unit::ModifyHealth(float hpModifier)
    {
        currentHP += hpModifier;
        if (currentHP <= 0)
        {
            alive = false;
        }
    }

    void Unit::DrawHP()
    {
        const float width = body.width;
        const float height = body.height;
        const Rectangle totalHP = {body.x + width / 2 - hp / 2, body.y - height / 2, hp, (width + height) / 6};
        Rectangle currentHpRect = {body.x + width / 2 - hp / 2, body.y - height / 2, currentHP, (width + height) / 6};

        DrawRectangleRec(totalHP, RAYWHITE);
        DrawRectangleRec(currentHpRect, RED);
    }

    void Unit::DrawBody()
    {
        Color color = GRAY;
        switch (team)
        {
        case player:
            color = BLUE;
            break;
        case enemy:
            color = RED;
            break;
        case neutral:
            color = RAYWHITE;
            break;
        }
        DrawRectangleRec(body, color);
    }

    bool Unit::IsSelected()
    {
        return selected;
    }

    void Unit::SetSelected(bool select)
    {
        selected = select;
    }

    Rectangle Unit::GetBody()
    {
        return body;
    }

    Team Unit::GetTeam()
    {
        return team;
    }

    bool Unit::IsAlive()
    {
        return alive;
    }

    void Unit::SetTarget(Unit* target)
    {
        this->target = target;
    }

    Unit* Unit::GetTarget()
    {
        return target;
    }
}
