#pragma once
#include <raylib.h>
#include <vector>

#include "EnemyController.h"
#include "../Entity/Unit.h"
#include "../Entity/Objects/Projectile.h"

class GameManager
{
public:
    GameManager();
    ~GameManager();
    void GameFlow();
    void Update();
    void Draw();

    static std::vector<Entity::Unit*> playerUnits;
    static std::vector<Entity::Unit*> enemyUnits;

private:
    
    Rectangle mouseSelection;
    Vector2 boxStart;
    Vector2 boxEnd;
    AIManager::EnemyController* enemyController;
    bool actionPerformed;
    
    void SpawnManager(char input);
    void MouseManager();
    void UnitsManager();
    void SelectUnit(Entity::Unit* unit) const;
    static void DeselectUnits();
    static void RemoveDeadUnits(std::vector<Entity::Unit*>& units);
    static void RemoveDeadProjectiles(std::vector<Objects::Projectile*>& projectile);
};
