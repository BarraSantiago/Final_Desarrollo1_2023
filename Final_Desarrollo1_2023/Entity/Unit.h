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
    virtual ~Unit();
    Unit();
    Unit(float hp, float attack, float range, float attackSpeed, float speed, Rectangle body, Team team);
    void Move();
    void SetDestination(Vector2 newDestination);
    void ModifyHealth(float hpModifier);
    void DrawHP();
    void DrawBody();
    virtual void Attack(Unit* target) = 0;
    bool IsSelected();
    void SetSelected(bool select);
    Rectangle GetBody();
    bool IsAlive();
    
protected:
    float hp;
    float currentHP;
    float attack;
    float range;
    float attackSpeed;
    float lastAttack;
    float speed;
    
    bool selected;
    bool alive;
    
    Team team;

    Vector2 destination{};
    
    Rectangle body;
    
};
