#include "Soldier.h"

#include <raymath.h>

Soldier::Soldier()
{
    hp = 100;
    attack = 20;
    range = 25;
    speed = 50;
    attackSpeed = 1;
    body = {100, 100, 50, 75};
}

Soldier::Soldier(float hp, float attack, float range, float speed, Rectangle body, Team team)
{
    this->hp = hp;
    this->attack = attack;
    this->range = range;
    this->speed = speed;
    this->body = body;
    this->team = team;
}

Soldier::~Soldier()
{
}

void Soldier::Attack()
{
    if (Vector2Distance({body.x, body.y}, {target->GetBody().x, target->GetBody().y}) > range) return;
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
