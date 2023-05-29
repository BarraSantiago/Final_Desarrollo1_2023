#pragma once
#include "..\DefaultEntity.h"

namespace Entity
{
    class Unit;
}

namespace Objects
{
    class Projectile : public Entity::DefaultEntity
    {
    public:
        Projectile();
        Projectile(float speed, float damage, Rectangle body,Vector2 direction, Entity::Team team);
        Projectile(Vector2 direction, Entity::Team team);
        ~Projectile() override;
        
        Rectangle GetBody() override;

        void Move();
        void SetTarget(Entity::Unit* target);
        void DrawBody() override;
        void Collide();
        bool isAlive();

    private:
        float speed;
        float damage;

        bool hasTarget;
        bool alive;

        Vector2 direction{};
        Entity::Team team;
        Entity::Unit* target;
        //float
    };
}
