#pragma once
#include "../Unit.h"

namespace Entity
{
    class Cavalry : public Unit
    {
    public:
        Cavalry();
        Cavalry(Vector2 position, Team team);
        Cavalry(float hp, float attack, float range, float speed, Rectangle body, Team team);
        void Attack() override;
        void SetDestination(Vector2 newDestination) override;
    private:
        bool inAttack;
        float speedAux;
        float specialSpeed;
        float attackFrames;
        Vector2 destinationAux;
        void SetDestinationToTarget();
    };
}
