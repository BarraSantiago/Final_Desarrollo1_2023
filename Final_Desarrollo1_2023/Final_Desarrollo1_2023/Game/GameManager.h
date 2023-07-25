#pragma once
#include <raylib.h>
#include <vector>

#include "EnemyController.h"
#include "../Entity/Unit.h"

class GameManager
{
public:
    GameManager();
    ~GameManager();
    void GameController();
    void Update();
    void Draw();

    static std::vector<Entity::Unit*> units;

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
    void DeselectUnits();
    void RemoveDeadUnits();
};
