#pragma once
#include <vector>

#include "../Entity/Unit.h"

class EnemyController
{
public:
    EnemyController(std::vector<Unit*> playerUnits);
    ~EnemyController();
    void Update();
    void Draw();
    std::vector<Unit*> GetEnemies();
private:
    std::vector<Unit*> enemyUnits;
    std::vector<Unit*> playerUnits;
};
