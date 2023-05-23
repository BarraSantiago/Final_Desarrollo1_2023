#pragma once
#include <raylib.h>

enum Team
{
    player,
    enemy,
    neutral
};

class Unit
{
public:
    virtual ~Unit() = 0;
    Unit();
    Unit(float hp, float attack, float range, float speed, Rectangle body, Team team);
    void Move();
    void SetDestination(Vector2 newDestination);
    void ModifyHealth(float hpModifier);
    void DrawHP();
    void DrawBody();
    virtual void Attack(Unit* target) = 0;
    bool IsSelected();
    void SetSelected(bool select);
    Rectangle GetBody();
    
protected:
    float hp;
    float currentHP;
    float attack;
    float range;
    float speed;
    
    bool selected;
    
    Team team;

    Vector2 destination{};
    
    Rectangle body;
    
};
