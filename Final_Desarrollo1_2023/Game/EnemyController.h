#pragma once
#include <vector>

#include "../Entity/Unit.h"

namespace AIManager
{
    class EnemyController
    {
    public:
        EnemyController(std::vector<Entity::Unit*> playerUnits);
        ~EnemyController();
        void Update();
        void Draw();
        std::vector<Entity::Unit*> GetEnemies();

        void SpawnArcher();
        void SpawnCavalry();
        void SpawnSoldier();

    private:
        std::vector<Entity::Unit*> enemyUnits;
        std::vector<Entity::Unit*> playerUnits;
    };
}
