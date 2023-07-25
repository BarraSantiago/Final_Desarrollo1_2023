#pragma once
#include <vector>

#include "../Entity/Unit.h"

namespace AIManager
{
    class EnemyController
    {
    public:
        EnemyController();
        ~EnemyController();
        void Update();
        void Draw();

        void SpawnArcher(Vector2 position);
        void SpawnCavalry(Vector2 position);
        void SpawnSoldier(Vector2 position);

    private:
        void UnitTargeting(Entity::Unit* Units);
        bool AreAnyUnitsAlive(Entity::Team team);
        
        float chaseRangeMultiplier = 8.0f;
    };
}
