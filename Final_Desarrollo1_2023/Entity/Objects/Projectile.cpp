#include "Projectile.h"

#include "../Unit.h"

namespace Objects
{
    Projectile::Projectile(): speed(130), damage(50), hasTarget(false), alive(true), direction({0, 0}),
                              team(Entity::neutral),
                              target(nullptr)
    {
    }

    Projectile::Projectile(float speed, float damage, Rectangle body, Vector2 direction, Entity::Team team):
        speed(speed), damage(damage), hasTarget(false), alive(true),
        direction(direction), team(team), target(nullptr)
    {
        this->body = body;
    }

    Projectile::Projectile(Vector2 direction, Entity::Team team): speed(130), damage(50), hasTarget(false),
                                                                  alive(true), target(nullptr)
    {
        this->direction = direction;
        this->team = team;
    }

    Projectile::~Projectile()
    {
    }

    void Projectile::Move()
    {
        body.x += direction.x * speed * GetFrameTime();
        body.y += direction.y * speed * GetFrameTime();
    }

    void Projectile::SetTarget(Entity::Unit* target)
    {
        this->target = target;
    }

    Rectangle Projectile::GetBody()
    {
        return body;
    }

    void Projectile::DrawBody()
    {
        Color color = GRAY;
        switch (team)
        {
        case Entity::player:
            color = BLUE;
            break;
        case Entity::enemy:
            color = RED;
            break;
        case Entity::neutral:
            color = RAYWHITE;
            break;
        }
        DrawRectangleRec(body, color);
    }

    void Projectile::Collide()
    {
        if(!hasTarget) return;
        
        target->ModifyHealth(-damage);
        alive = false;
    }

    bool Projectile::isAlive()
    {
        return alive;
    }
}
