﻿#pragma once
#include "DefaultEntity.h"

namespace Entity
{
    enum Team
    {
        player,
        enemy,
        neutral
    };
    class Unit : public DefaultEntity
    {
    public:
        virtual ~Unit();
        Unit();
        Unit(float hp, float attack, float range, float attackSpeed, float speed, Rectangle body, Team team);
        void Move();
        void SetDestination(Vector2 newDestination);
        void ModifyHealth(float hpModifier);
        void DrawHP();
        virtual void Attack() = 0;
        bool IsSelected();
        Unit* GetTarget();
        Team GetTeam();
        bool IsAlive();
        void SetSelected(bool select);
        void SetTarget(Unit* target);
        Rectangle GetBody() override;
        void DrawBody() override;

    protected:
        float hp;
        float currentHP;
        float attack;
        float range;
        float attackSpeed;
        float attackCooldown;
        float speed;
        float distanceX;
        float distanceY;

        bool selected;
        bool alive;

        Team team;

        Unit* target;

        Vector2 destination{};

    };
}
