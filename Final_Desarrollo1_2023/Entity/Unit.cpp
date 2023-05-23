#include "Unit.h"

#include <cmath>
#include <cfloat>
#include "raymath.h"

Unit::~Unit()
= default;

Unit::Unit(): hp(100), currentHP(100), attack(20), range(5), attackSpeed(1), speed(50), selected(false), alive(true),
              team(player), destination({200, 200}), body({200, 200, 100, 100})
{
}

Unit::Unit(float hp, float attack, float range, float attackSpeed, float speed, Rectangle body, Team team) :
    hp(hp), currentHP(hp), attack(attack), range(range), attackSpeed(attackSpeed),
    speed(speed), selected(false), alive(true), team(team), body(body)
{
    destination = {body.x, body.y};
}

void Unit::Move()
{
    Vector2 direction = Vector2Normalize(destination); //Normalize vector to use as unit's direction

    if (!(Vector2Distance({body.x, body.y}, destination) < speed))
    {
        body.x += direction.x * speed * GetFrameTime();

        body.y += direction.y * speed * GetFrameTime();
    }
}

void Unit::SetDestination(Vector2 newDestination)
{
    destination = Vector2Subtract(newDestination, {body.x, body.y});
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
    const float height = body.height;
    const float width = body.width;
    const Rectangle totalHP = {body.x + width / 2 - hp / 2, body.y - height / 2, hp, width / 4};
    Rectangle currentHpRect = {body.x + width / 2 - hp / 2, body.y - height / 2, currentHP, width / 4};

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

Unit* Unit::GetTarget()
{
    return target;
}
