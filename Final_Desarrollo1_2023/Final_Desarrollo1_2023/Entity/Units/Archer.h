#pragma once
#include <vector>

#include "../Unit.h"
#include "../Objects/Projectile.h"

class Archer : public Entity::Unit
{
public:
    Archer(Entity::Team team);
    Archer(float hp, float attack, float range, float attackSpeed, float speed, const Rectangle& body,
           Entity::Team team, float proyectileSpeed);
    Archer(Vector2 position, Entity::Team team);
    ~Archer() override;
    
    void Attack() override;
    static std::vector<Objects::Projectile*> GetProjectiles();
    
private:
    float proyectileSpeed;
    static std::vector<Objects::Projectile*> projectiles;
};
