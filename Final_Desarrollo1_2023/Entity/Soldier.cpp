#include "Soldier.h"

#include <raymath.h>

#include "CheckRange.h"

namespace Entity
{
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
        if (Check::InRange(body, target->GetBody(), range)) return;
        if (Check::SameTeam(team, target->GetTeam())) return;

        if (attackCooldown <= 0)
        {
            target->ModifyHealth(-attack);
            attackCooldown = attackSpeed;
        }
        else
        {
            attackCooldown -= attackSpeed * GetFrameTime();
        }
    }
}
