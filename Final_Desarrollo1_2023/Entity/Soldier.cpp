#include "Soldier.h"

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

void Soldier::Attack(Unit* target)
{
    if (lastAttack <= 0)
    {
        target->ModifyHealth(attack);
        lastAttack = attackSpeed;
    }
    else
    {
        lastAttack -= attackSpeed * GetFrameTime();
    }
}
