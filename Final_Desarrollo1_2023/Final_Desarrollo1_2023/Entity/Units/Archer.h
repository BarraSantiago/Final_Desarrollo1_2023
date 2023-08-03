#pragma once
#include <vector>

#include "../Unit.h"
#include "../Objects/Projectile.h"

namespace Entity
{
    class Archer : public Unit
    {
    public:
        Archer(Team team);
        Archer(float hp, float attack, float range, float attackSpeed, float speed, const Rectangle& body,
               Team team, float proyectileSpeed);
        Archer(Vector2 position, Team team, Texture2D texture);
        ~Archer() override;

        void Attack() override;
        static std::vector<Objects::Projectile*> projectiles;

    private:
        float proyectileSpeed;
    };
}
