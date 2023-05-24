#pragma once
#include "Unit.h"

namespace Entity
{
    class Soldier : public Unit
    {
    public:
        Soldier();
        Soldier(float hp, float attack, float range, float speed, Rectangle body, Team team);
        Soldier(Vector2 position, Team team);
        ~Soldier() override;
        void Attack() override;
    };
}
