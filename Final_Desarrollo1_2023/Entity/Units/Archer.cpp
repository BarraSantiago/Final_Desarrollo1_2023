#include "Archer.h"

#include "../CheckRange.h"

Archer::Archer(Entity::Team team)
{
    hp = 100;
    attack = 20;
    speed = 35;
    range = 150 + (body.width + body.height) / 2;
    attackSpeed = 1;
    body = {100, 100, 40, 80};
    proyectileSpeed = speed * 2;
    this->team = team;
}

Archer::Archer(float hp, float attack, float range, float attackSpeed, float speed, const Rectangle& body,
               Entity::Team team, float proyectileSpeed)
{
    this->hp = hp;
    this->attack = attack;
    this->range = range;
    this->speed = speed;
    this->attackSpeed = attackSpeed;
    this->body = body;
    this->team = team;
    this->proyectileSpeed = proyectileSpeed;
}

Archer::Archer(Vector2 position, Entity::Team team)
{
    hp = 100;
    attack = 20;
    speed = 35;
    attackSpeed = 1;
    proyectileSpeed = speed * 2;
    body = {position.x, position.y, 40, 80};
    range = 150 + (body.width + body.height) / 2;
    this->team = team;
}

Archer::~Archer()
{
}

void Archer::Attack()
{
    if (Check::InRange(body, target->GetBody(), range)) return;
    if (Check::SameTeam(team, target->GetTeam())) return;

    if (!target->IsAlive()) return;

    //if attack is in cooldown, no extra calculation is made
    if (attackCooldown > 0)
    {
        attackCooldown -= attackSpeed * GetFrameTime();
        return;
    }

    target->ModifyHealth(-attack);
    attackCooldown = attackSpeed;
}
