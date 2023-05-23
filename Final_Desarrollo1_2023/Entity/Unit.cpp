#include "Unit.h"

#include <cmath>
#include <cfloat>
#include "raymath.h"

Unit::Unit(): hp(100), currentHP(100), attack(20), range(5), speed(50), selected(false), team(player),
              destination({200, 200}),
              body({200, 200, 100, 100})
{
}

Unit::Unit(float hp, float attack, float range, float speed, Rectangle body, Team team) : hp(hp), currentHP(hp),
    attack(attack),
    range(range), speed(speed), selected(false), team(team), body(body)
{
    destination = {body.x, body.y};
}

void VectorDifference(float& x, float& y, Vector2& b)
{
    float diff_x = x - b.x;
    float diff_y = y - b.y;

    float sqrmagX = diff_x * diff_x;

    if (sqrmagX < FLT_EPSILON * FLT_EPSILON)
    {
        b.x = 0;
    }

    float sqrmagY = diff_y * diff_y;

    if (sqrmagY < FLT_EPSILON * FLT_EPSILON)
    {
        b.y = 0;
    }
}

void Unit::Move()
{
    Vector2 normVector = Vector2Normalize(destination); //Normalize vector to use as unit's direction

    body.x += normVector.x * speed * GetFrameTime();
    body.y += normVector.y * speed * GetFrameTime();

    VectorDifference(body.x, body.y, destination);
}

void Unit::SetDestination(Vector2 newDestination)
{
    this->destination.x = newDestination.x - body.x;
    this->destination.y = newDestination.y - body.y;
}

void Unit::ModifyHealth(float hpModifier)
{
    currentHP += hpModifier;
}

void Unit::DrawHP()
{
    const float height = body.height;
    const Rectangle totalHP = {body.x + height / 2 - hp / 2, body.y - height / 2, hp, body.width / 4};
    Rectangle currentHpRect = {body.x + height / 2 - hp / 2, body.y - height / 2, currentHP, body.width / 4};

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
