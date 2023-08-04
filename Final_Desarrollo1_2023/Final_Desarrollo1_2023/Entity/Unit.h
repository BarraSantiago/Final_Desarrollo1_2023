#pragma once
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
        void DrawHP() const;
        virtual void Attack() = 0;
        bool IsSelected() const;
        Unit* GetTarget();
        Team GetTeam() const;
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

        const float hpBarHeight = 20;

        bool selected;
        bool alive;

        Team team;
        Color color{};
        const Color selectionColor = YELLOW;

        Unit* target;

        Vector2 destination{};
        Vector2 direction{};
        Texture2D texture;
    };
}
