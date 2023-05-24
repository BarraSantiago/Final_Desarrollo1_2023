#pragma once
#include <raylib.h>
namespace Entity
{
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
        virtual void Attack() = 0;
        bool IsSelected();
        void SetSelected(bool select);
        Rectangle GetBody();
        Team GetTeam();
        bool IsAlive();
        void SetTarget(Unit* target);
        Unit* GetTarget();

    protected:
        float hp;
        float currentHP;
        float attack;
        float range;
        float attackSpeed;
        float attackCooldown;
        float speed;
        float destinationDistance;

        bool selected;
        bool alive;

        Team team;

        Unit* target;

        Vector2 destination{};

        Rectangle body;
    };
}