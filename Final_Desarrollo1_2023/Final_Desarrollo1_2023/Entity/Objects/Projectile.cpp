#include "Projectile.h"

#include <raymath.h>

#include "cmath"
#include "../Unit.h"
#include "../../Game/Collisions.h"
#include "../../Game/GameManager.h"

namespace Objects
{
    Projectile::Projectile(): speed(130), damage(50), alive(true), direction({0, 0}),
                              team(Entity::neutral),
                              target(nullptr)
    {
        color = GRAY;
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
    }

    Projectile::Projectile(float speed, float damage, Rectangle body, Vector2 direction, Entity::Team team):
        speed(speed), damage(damage), alive(true),
        direction(direction), team(team), target(nullptr)
    {
        this->body = body;
        color = GRAY;
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
    }

    Projectile::Projectile(Vector2 direction, Vector2 origin, Entity::Team team): speed(35), damage(30), alive(true),
        target(nullptr)
    {
        this->destination = direction;
        this->direction = Vector2Normalize(Vector2Subtract(direction, {body.x, body.y}));
        this->team = team;
        
        body.x = origin.x;
        body.y = origin.y;
        body.width = 50;
        body.height = 25;

        color = GRAY;
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
    }

    Projectile::~Projectile()
    = default;
    
    void Projectile::Move()
    {
        body.x += direction.x * speed * GetFrameTime();
        body.y += direction.y * speed * GetFrameTime();

        if (team == Entity::player)
        {
            for (Entity::Unit* unit : GameManager::enemyUnits)
            {
                if (Collision::AABBCollision(this, unit))
                {
                    SetTarget(unit);
                    Collide();
                    break;
                }
            }
        }
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
        DrawRectangleRec(body, color);
    }

    void Projectile::Collide()
    {
        target->ModifyHealth(-damage);
        alive = false;
    }

    bool Projectile::IsAlive()
    {
        return alive;
    }
}
