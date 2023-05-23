#pragma once
#include "Unit.h"

class Soldier : public Unit
{
public:
    Soldier();
    Soldier(float hp, float attack, float range, float speed, Rectangle body, Team team);
    ~Soldier() override;
    void Attack(Unit* target) override;
};
