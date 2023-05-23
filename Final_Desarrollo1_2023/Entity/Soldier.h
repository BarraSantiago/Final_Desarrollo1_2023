#pragma once
#include "Unit.h"

class Soldier : public Unit
{
public:
    Soldier();
    ~Soldier() override;
    void Attack(Unit* target) override;
};
