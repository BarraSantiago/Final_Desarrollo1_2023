#pragma once
#include "../Unit.h"

class Archer : public Entity::Unit
{
public:
    Archer(Entity::Team team);
    Archer(float hp, float attack, float range, float attackSpeed, float speed, const Rectangle& body,
           Entity::Team team, float proyectileSpeed);
    Archer(Vector2 position, Entity::Team team);

    ~Archer() override;
    void Attack() override;

private:
    float proyectileSpeed;
};
