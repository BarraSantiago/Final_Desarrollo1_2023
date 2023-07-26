#include "Archer.h"

#include "..\Checks.h"
#include "../Objects/Projectile.h"

namespace Entity
{
    std::vector<Objects::Projectile*> Archer::projectiles;

    Archer::Archer(Team team)
    {
        hp = 100;
        attack = 20;
        speed = 35;
        range = 150 + (body.width + body.height) / 2;
        attackSpeed = 1;
        body = {100, 100, 40, 80};
        proyectileSpeed = speed * 2;

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

    Archer::Archer(float hp, float attack, float range, float attackSpeed, float speed, const Rectangle& body,
                   Team team, float proyectileSpeed)
    {
        this->hp = hp;
        this->attack = attack;
        this->range = range;
        this->speed = speed;
        this->attackSpeed = attackSpeed;
        this->body = body;
        this->team = team;
        this->proyectileSpeed = proyectileSpeed;

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

    Archer::Archer(Vector2 position, Team team)
    {
        hp = 100;
        attack = 20;
        speed = 35;
        attackSpeed = 1;
        proyectileSpeed = speed * 2;
        body = {position.x, position.y, 40, 80};
        range = 150 + (body.width + body.height) / 2;
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

    Archer::~Archer()
    = default;

    void Archer::Attack()
    {
        //if attack is in cooldown, no extra calculation is made
        if (attackCooldown > 0)
        {
            attackCooldown -= attackSpeed * GetFrameTime();
            return;
        }
        if (!target) return;
        if (Check::InRange(body, target->GetBody(), range)) return;
        if (team == target->GetTeam()) return;

        projectiles.push_back(new Objects::Projectile({target->body.x, target->body.y}, {body.x, body.y}, team));

        attackCooldown = attackSpeed;
    }
}
