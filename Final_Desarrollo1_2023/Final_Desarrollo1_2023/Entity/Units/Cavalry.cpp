#include "Cavalry.h"

#include <raymath.h>

#include "..\Checks.h"

namespace Entity
{
    float attackFramesAux = 5;

    Cavalry::Cavalry(): inAttack(false), destinationAux()
    {
        hp = 75;
        currentHP = hp;
        attack = 35;
        speed = 50;
        specialSpeed = speed * 4;
        speedAux = speed;
        attackSpeed = 1;
        range = 25 + (body.width + body.height) / 2;
        attackFrames = attackSpeed / 2;
        attackCooldown = 0;

        body = {100, 100, 75, 50};

        direction = {0, 0};

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

    Cavalry::Cavalry(Vector2 position, Team team, Texture2D newTexture): inAttack(false), destinationAux()
    {
        texture = newTexture;
        hp = 75;
        currentHP = hp;
        attack = 35;
        speed = 50;
        specialSpeed = speed * 4;
        speedAux = speed;
        attackSpeed = 1;
        body = {
            position.x, position.y, static_cast<float>(newTexture.width) * 0.1f, static_cast<float>(newTexture.height) * 0.1f
        };
        range = 25 + (body.width + body.height) / 2;
        attackFrames = attackSpeed / 2;
        direction = {0, 0};
        attackCooldown = 0;

        this->team = team;

        switch (team)
        {
        case player:
            color = WHITE;
            break;
        case enemy:
            color = DARKGRAY;
            break;
        case neutral:
            color = RAYWHITE;
            break;
        }
    }

    Cavalry::Cavalry(float hp, float attack, float range, float speed, Rectangle body, Team team): inAttack(false),
        specialSpeed(speed * 4), destinationAux()
    {
        this->hp = hp;
        currentHP = hp;
        this->attack = attack;
        this->range = range;
        this->speed = speed;
        speedAux = speed;
        attackSpeed = 1;
        this->body = body;
        this->team = team;
        attackFrames = attackSpeed / 2;
        direction = {0, 0};
        attackCooldown = 0;

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

    void Cavalry::Attack()
    {
        if (target == nullptr) return;

        if (attackCooldown > 0)
        {
            attackCooldown -= attackSpeed * GetFrameTime();
            attackFrames -= GetFrameTime();
            return;
        }

        //if attack is in cooldown, no extra calculation is made
        if (attackFrames <= 0 && inAttack)
        {
            inAttack = false;
            speed = speedAux;
            direction = destinationAux;
        }

        if (Check::InRange(body, target->GetBody(), range)) return;
        if (team == target->GetTeam()) return;


        //Finishes special attack behaviour
        if (!target->IsAlive()) return;

        SetDestinationToTarget();

        speed = specialSpeed;

        target->ModifyHealth(-attack);

        attackCooldown = attackSpeed;
        destinationAux = direction;
        attackFrames = attackSpeed / 2;
        inAttack = true;
    }

    void Cavalry::SetDestination(Vector2 newDestination)
    {
        if (attackCooldown > 0)
        {
            destinationAux = newDestination;
        }
        else
        {
            Unit::SetDestination(newDestination);
        }
    }

    void Cavalry::SetDestinationToTarget()
    {
        float unitX = body.x + body.width / 2;
        float unitY = body.y + body.height / 2;

        float targetX = target->GetBody().x + target->GetBody().width / 2;
        float targetY = target->GetBody().y + target->GetBody().height / 2;

        //sets direction to enemy unit
        direction = Vector2Subtract({targetX, targetY}, {unitX, unitY});
    }
}
