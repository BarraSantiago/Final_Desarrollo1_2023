﻿#pragma once
#include "DefaultEntity.h"

namespace Entity
{
    
    class Unit : public DefaultEntity
    {
    public:
        ~Unit() override;
        Unit();
        void Move();
        virtual void SetDestination(Vector2 newDirection);
        void ModifyHealth(float hpModifier);
        void DrawHP();
        virtual void Attack() = 0;
        bool IsSelected();
        Unit* GetTarget();
        Team GetTeam();
        bool IsAlive() override;
        void SetSelected(bool select);
        void SetTarget(Unit* target);
        Rectangle GetBody() override;
        void DrawBody() override;
        float GetRange() const;
        Vector2 GetDestination() const;
        
    protected:
        float hp;
        float currentHP;
        float attack;
        float range;
        float attackSpeed;
        float attackCooldown;
        float speed;

        bool selected;
        bool alive;

        Team team;
        Color color;

        Unit* target;

        Vector2 destination{};
        Vector2 direction{};

    };
}