#include "Unit.h"

#include <cmath>
#include <float.h>

Unit::~Unit()
{
}

Unit::Unit(): hp(100), currentHP(100), attack(20), range(5), speed(10), selected(false), team(player),
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

void Unit::Move()
{
    body.x += destination.x * GetFrameTime();
    body.y += destination.y * GetFrameTime();

    float diff_x = body.x - destination.x;
    float diff_y = body.y - destination.y;
    
    float sqrmagX = diff_x * diff_x;
    
    if (sqrmagX < FLT_EPSILON * FLT_EPSILON)
    {
        destination.x = 0;
    }
    
    
    float sqrmagY = diff_y * diff_y;
    if (sqrmagY < FLT_EPSILON * FLT_EPSILON)
    {
        destination.y = 0;
    }
}

void Unit::SetDestination(Vector2 destination)
{
    this->destination.x = destination.x - body.x;
    this->destination.y = destination.y - body.y;
    float magnitude = sqrt(destination.x * destination.x + destination.y * destination.y);

    if (magnitude != 0)
    {
        destination.x /= magnitude;
        destination.y /= magnitude;
    }
}

void Unit::ModifyHealth(float hpModifier)
{
    currentHP += hpModifier;
}

void Unit::DrawHP()
{
    Rectangle totalHP = {body.x + body.height / 2 - hp / 2, body.y - body.height / 2, hp, body.width / 4};
    Rectangle currentHpRect = {body.x + body.height / 2 - hp / 2, body.y - body.height / 2, currentHP, body.width / 4};
    DrawRectangleRec(totalHP, RAYWHITE);
    DrawRectangleRec(currentHpRect, RED);
}

void Unit::DrawBody()
{
    Color color;
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
    default:
        color = GRAY;
    }
    DrawRectangleRec(body, color);
}

void Unit::Attack(Unit* target)
{
    target->ModifyHealth(-attack);
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
