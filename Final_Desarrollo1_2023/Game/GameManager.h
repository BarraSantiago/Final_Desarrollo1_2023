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
private:
    Rectangle mouseSelection;
    Vector2 boxStart;
    Vector2 boxEnd;
    AIManager::EnemyController* enemyController;
    std::vector<Entity::Unit*> units;
    
};
