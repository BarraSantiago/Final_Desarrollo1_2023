#include "Soldier.h"

#include "..\Checks.h"

namespace Entity
{
    Soldier::Soldier()
    {
        hp = 150;
        attack = 20;
        speed = 50;
        attackSpeed = 1;
        body = {100, 100, 50, 75};
        range = 25 + (body.width + body.height) / 2;

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

    Soldier::Soldier(float hp, float attack, float range, float speed, Rectangle body, Team team)
    {
        this->hp = hp;
        this->attack = attack;
        this->range = range;
        this->speed = speed;
        attackSpeed = 1;
        this->body = body;
        this->team = team;

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

    Soldier::Soldier(Vector2 position, Team team)
    {
        texture = LoadTexture("../res/red-knight.png");
        hp = 100;
        attack = 20;
        speed = 50;
        attackSpeed = 1;
        body = {
            position.x, position.y, static_cast<float>(texture.width) * 0.1f, static_cast<float>(texture.height) * 0.1f
        };
        range = 25 + (body.width + body.height) / 2;
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

    Soldier::~Soldier()
    = default;

    void Soldier::Attack()
    {
        if (attackCooldown > 0)
        {
            attackCooldown -= attackSpeed * GetFrameTime();
            return;
        }
        if (target == nullptr) return;
        if (Check::InRange(body, target->GetBody(), range)) return;
        if (team == target->GetTeam()) return;

        //if attack is in cooldown, no extra calculation is made


        target->ModifyHealth(-attack);
        attackCooldown = attackSpeed;
    }
}
