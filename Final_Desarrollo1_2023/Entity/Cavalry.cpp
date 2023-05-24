#include "Cavalry.h"

#include <raymath.h>

#include "CheckRange.h"

namespace Entity
{
    Cavalry::Cavalry(): isAttacking(false), destinationAux()
    {
        hp = 75;
        attack = 35;
        speed = 50;
        speedAux = speed;
        attackSpeed = 1;
        specialSpeed = 120;
        body = {100, 100, 75, 50};
        range = 25 + (body.width + body.height) / 2;
        attackFrames = attackSpeed / 2;
        destination = {0, 0};
    }

    Cavalry::Cavalry(float x, float y): isAttacking(false), destinationAux()
    {
        hp = 75;
        attack = 35;
        speed = 50;
        speedAux = speed;
        attackSpeed = 1;
        specialSpeed = 120;
        body = {x, y, 70, 50};
        range = 25 + (body.width + body.height) / 2;
        attackFrames = attackSpeed / 2;
        destination = {0, 0};
    }

    Cavalry::Cavalry(float hp, float attack, float range, float speed, Rectangle body, Team team): specialSpeed(100),
        isAttacking(false),
        destinationAux()
    {
        this->hp = hp;
        this->attack = attack;
        this->range = range;
        this->speed = speed;
        speedAux = speed;
        attackSpeed = 1;
        this->body = body;
        this->team = team;
        attackFrames = attackSpeed / 2;
        destination = {0, 0};
    }

    void Cavalry::Attack()
    {
        if (Check::InRange(body, target->GetBody(), range)) return;
        if (Check::SameTeam(team, target->GetTeam())) return;

        //Finishes special attack behaviour
        if (attackFrames <= 0 && isAttacking)
        {
            speed = speedAux;
            destination = destinationAux;
            isAttacking = false;
        }
        if (!target->IsAlive()) return;

        //if attack is in cooldown, no extra calculation is made
        if (attackCooldown > 0)
        {
            attackCooldown -= attackSpeed * GetFrameTime();
            return;
        }

        float unitX = body.x + body.width / 2;
        float unitY = body.y + body.height / 2;

        float targetX = target->GetBody().x + target->GetBody().width / 2;
        float targetY = target->GetBody().y + target->GetBody().height / 2;


        target->ModifyHealth(-attack);

        attackCooldown = attackSpeed;
        destinationAux = destination;

        //sets direction to enemy unit
        destination = Vector2Subtract({targetX + range / 2, targetY + range / 2}, {unitX, unitY});
        speed = specialSpeed;
        isAttacking = true;
    }
}
