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
        static void Update();
        static void Draw();

        void SpawnArcher(Vector2 position) const;
        void SpawnCavalry(Vector2 position) const;
        void SpawnSoldier(Vector2 position) const;

    private:
        Texture2D solTexture{};
        Texture2D arcTexture{};
        Texture2D cavTexture{};
        static void UnitTargeting(Entity::Unit* Units);
        static bool AreAnyUnitsAlive(const std::vector<Entity::Unit*>& units);
        
        const float chaseRangeMultiplier = 8.0f;
    };
}
