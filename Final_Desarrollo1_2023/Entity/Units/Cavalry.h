﻿#pragma once
#include "../Unit.h"

namespace Entity
{
    class Cavalry : public Unit
    {
    public:
        Cavalry();
        Cavalry(float x, float y);
        Cavalry(float hp, float attack, float range, float speed, Rectangle body, Team team);
        void Attack() override;

    private:
        float speedAux;
        float specialSpeed;
        float attackFrames;
        Vector2 destinationAux;
        void SetDestinationToTarget();
    };
}