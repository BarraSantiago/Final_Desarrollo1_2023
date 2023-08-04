#include "Projectile.h"

#include <raymath.h>

#include "../Unit.h"
#include "../../Game/Collisions.h"
#include "../../Game/GameManager.h"

Texture2D Objects::Projectile::redTexture;
Texture2D Objects::Projectile::blueTexture;

namespace Objects
{
    Projectile::Projectile(): speed(130), damage(50), alive(true), direction({0, 0}),
                              team(Entity::neutral), target(nullptr)
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

    Projectile::Projectile(Vector2 direction, Vector2 origin, Entity::Team team): speed(70), damage(30), alive(true),
        target(nullptr)
    {
        this->destination = direction;
        this->direction = Vector2Normalize(Vector2Subtract(direction, origin));
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

        switch (team)
        {
        case Entity::player:
            CheckCollision(GameManager::enemyUnits);
            break;
        case Entity::enemy:
            CheckCollision(GameManager::playerUnits);

            break;
        case Entity::neutral:
        default:
            break;
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
        const float scale = 0.05f;
        const float frameWidth = static_cast<float>(blueTexture.width);
        const float frameHeight = static_cast<float>(blueTexture.height);

        const Vector2 origin = {
            static_cast<float>(blueTexture.width) * scale, static_cast<float>(blueTexture.height) * scale
        };

        const Rectangle sourceRec = {0, 0, frameWidth, frameHeight};
        const Rectangle invserseSourceRec = {sourceRec.x, sourceRec.y, -sourceRec.width, sourceRec.height};
        const Rectangle destRec = {body.x + body.width / 2, body.y + body.height / 2, body.width, body.height};

        const bool movingRight = direction.x > 0;

        const Texture2D currentTexture = team == Entity::player ? blueTexture : redTexture;
        DrawTexturePro(currentTexture, movingRight ? sourceRec : invserseSourceRec, destRec, origin, 0, RAYWHITE);
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

    void Projectile::CheckCollision(const std::vector<Entity::Unit*>& units)
    {
        for (Entity::Unit* unit : units)
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
