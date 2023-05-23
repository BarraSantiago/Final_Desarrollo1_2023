#include "Soldier.h"

#include <raymath.h>

Soldier::Soldier()
{
    hp = 100;
    attack = 20;
    speed = 50;
    attackSpeed = 1;
    body = {100, 100, 50, 75};
    range = 25 + (body.width + body.height) / 2;
}

Soldier::Soldier(float hp, float attack, float range, float speed, Rectangle body, Team team)
{
    this->hp = hp;
    this->attack = attack;
    this->range = range;
    this->speed = speed;
    attackSpeed = 1;
    this->body = body;
    this->team = team;
}

Soldier::~Soldier()
{
}

void Soldier::Attack()
{
    float unitX = body.x + body.width / 2;
    float unitY = body.y + body.height / 2;

    float targetX = target->GetBody().x + target->GetBody().width / 2;
    float targetY = target->GetBody().y + target->GetBody().height / 2;

    //if target isn't in range, no calculation is made
    if (Vector2Distance({unitX, unitY}, {targetX, targetY}) > range) return;

    if (target->GetTeam() == team) return;

    if (lastAttack <= 0)
    {
        target->ModifyHealth(-attack);
        lastAttack = attackSpeed;
    }
    else
    {
        lastAttack -= attackSpeed * GetFrameTime();
    }
}

void Soldier::SetTarget(Unit* target)
{
    this->target = target;
}
