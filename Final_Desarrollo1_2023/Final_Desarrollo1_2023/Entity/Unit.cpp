#include "Unit.h"

#include <cmath>
#include "raymath.h"

namespace Entity
{
    Unit::~Unit()
    = default;

    Unit::Unit(): hp(100), currentHP(hp), attack(20), range(5), attackSpeed(1), attackCooldown(1), speed(50),
                  selected(false), alive(true), team(player),
                  target(nullptr), direction({200, 200})
    {
        body = {200, 200, 100, 100};
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
    }

    bool Vector2IsEqual(const Vector2& vec1, const Vector2& vec2, float tolerance = 0.01f)
    {
        return (std::fabs(vec1.x - vec2.x) <= tolerance) && (std::fabs(vec1.y - vec2.y) <= tolerance);
    }

    void Unit::Move()
    {
        Vector2 position = {body.x, body.y};

        if (!Vector2IsEqual(position, destination))
        {
            float distance = speed * GetFrameTime();
            Vector2 movementDelta = Vector2Scale(Vector2Normalize(direction), distance);
            position = Vector2Add({body.x, body.y}, movementDelta);
            body.x = position.x;
            body.y = position.y;
        }
    }

    void Unit::SetDestination(Vector2 newDirection)
    {
        this->destination = newDirection;
        direction = Vector2Subtract(newDirection, {body.x, body.y});
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
        const float lineWidth = ((body.width + body.height) / 2) / 10;

        DrawRectangleRec(body, color);

        if (selected)
        {
            DrawRectangleLinesEx(body, lineWidth, YELLOW);
        }
    }

    float Unit::GetRange() const
    {
        return range;
    }

    Vector2 Unit::GetDestination() const
    {
        return direction;
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
        if (target->GetTeam() != team)
        {
            this->target = target;
        }
    }

    Unit* Unit::GetTarget()
    {
        return target;
    }
}
