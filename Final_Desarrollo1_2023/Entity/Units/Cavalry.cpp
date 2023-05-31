#include "Cavalry.h"

#include <raymath.h>

#include "../CheckRange.h"

namespace Entity
{
    float attackFramesAux = 5;

    Cavalry::Cavalry(): destinationAux()
    {
        hp = 75;
        attack = 35;
        speed = 50;
        specialSpeed = speed * 4;
        speedAux = speed;
        attackSpeed = 1;
        range = 25 + (body.width + body.height) / 2;
        attackFrames = attackSpeed / 2;

        body = {100, 100, 75, 50};

        destination = {0, 0};
    }

    Cavalry::Cavalry(Vector2 position, Team team): destinationAux()
    {
        hp = 75;
        attack = 35;
        speed = 50;
        specialSpeed = speed * 4;
        speedAux = speed;
        attackSpeed = 1;
        body = {position.x, position.y, 70, 50};
        range = 25 + (body.width + body.height) / 2;
        attackFrames = attackSpeed / 2;
        destination = {0, 0};
        this->team = team;
    }

    Cavalry::Cavalry(float hp, float attack, float range, float speed, Rectangle body, Team team):
        specialSpeed(speed * 4), destinationAux()
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
        if (attackCooldown > 0)
        {
            attackCooldown -= attackSpeed * GetFrameTime();
            attackFrames -= GetFrameTime();
            return;
        }
        if (attackFrames <= 0 && inAttack)
        {
            inAttack = false;
            speed = speedAux;
            destination = destinationAux;
        }
        //if attack is in cooldown, no extra calculation is made
        
        if (Check::InRange(body, target->GetBody(), range)) return;
        if (Check::SameTeam(team, target->GetTeam())) return;

        
        //Finishes special attack behaviour
        if (!target->IsAlive()) return;

        

        SetDestinationToTarget();

        speed = specialSpeed;

        target->ModifyHealth(-attack);

        attackCooldown = attackSpeed;
        destinationAux = destination;
        attackFrames = attackSpeed / 2;
        inAttack = true;
    }

    void Cavalry::SetDestination(Vector2 newDestination)
    {
        if (attackCooldown > 0) return;
        Unit::SetDestination(newDestination);
    }

    void Cavalry::SetDestinationToTarget()
    {
        float unitX = body.x + body.width / 2;
        float unitY = body.y + body.height / 2;

        float targetX = target->GetBody().x + target->GetBody().width / 2;
        float targetY = target->GetBody().y + target->GetBody().height / 2;

        //sets direction to enemy unit
        destination = Vector2Subtract({targetX, targetY}, {unitX, unitY});
    }
}
