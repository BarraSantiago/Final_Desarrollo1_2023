#pragma once
#include "../Unit.h"
#include "../DefaultEntity.h"

namespace Objects
{
    class Projectile : public Entity::DefaultEntity
    {
    public:
        Projectile();
        Projectile(float speed, float damage, Rectangle body,Vector2 direction, Entity::Team team);
        Projectile(Vector2 direction, Vector2 origin, Entity::Team team);
        ~Projectile() override;
        
        Rectangle GetBody() override;

        void Move();
        void SetTarget(Entity::Unit* unit);
        void DrawBody() override;
        void Collide();
        bool IsAlive() override;

    private:
        float speed;
        float damage;

        bool alive;

        Vector2 direction{};
        Vector2 destination{};

        Entity::Team team;
        Entity::Unit* target;
        
        Color color{};
    };
}
