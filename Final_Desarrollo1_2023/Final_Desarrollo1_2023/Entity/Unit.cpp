#include "Unit.h"

#include <cmath>
#include "raymath.h"

namespace Entity
{
    Unit::~Unit()
    {
        UnloadTexture(texture);
    }

    Unit::Unit(): hp(100), currentHP(hp), attack(20), range(5), attackSpeed(1), attackCooldown(1), speed(50),
                  selected(false), alive(true), team(player),
                  target(nullptr), direction({200, 200}), texture()
    {
        switch (team)
        {
        case player:
            color = RAYWHITE;
            break;
        case enemy:
            color = RED;
            break;
        case neutral:
            color = GRAY;
            break;
        }
    }

    bool Vector2IsEqual(const Vector2& vec1, const Vector2& vec2, float tolerance = 0.01f)
    {
        return (std::fabs(vec1.x - vec2.x) <= tolerance) && (std::fabs(vec1.y - vec2.y) <= tolerance);
    }

    void Unit::Move()
    {
        Vector2 position = {body.x, body.y};

        if (!Vector2IsEqual(position, destination))
        {
            float distance = speed * GetFrameTime();
            Vector2 movementDelta = Vector2Scale(Vector2Normalize(direction), distance);
            position = Vector2Add({body.x, body.y}, movementDelta);
            body.x = position.x;
            body.y = position.y;
        }
    }

    void Unit::SetDestination(Vector2 newDirection)
    {
        this->destination = newDirection;
        direction = Vector2Subtract(newDirection, {body.x, body.y});
    }

    void Unit::ModifyHealth(float hpModifier)
    {
        currentHP += hpModifier;
        if (currentHP <= 0)
        {
            alive = false;
        }
    }

    void Unit::DrawHP() const
    {
        const float width = body.width;
        const float height = body.height;
        float xPos = body.x + width / 2 - hp / 2;
        float yPos = body.y - height / 2;
        
        const Rectangle totalHP = {xPos, yPos, hp, HPBARHEIGHT};
        Rectangle currentHpRect = {xPos, yPos, currentHP, HPBARHEIGHT};

        DrawRectangleRec(totalHP, RAYWHITE);
        DrawRectangleRec(currentHpRect, RED);
    }
    Rectangle TextureToSourceRec(Texture2D texture)
    {
        int frameWidth = texture.width;
        int frameHeight = texture.height;
        return {0.0f, 0.0f, static_cast<float>(frameWidth), static_cast<float>(frameHeight)};
    }
    void Unit::DrawBody()
    {
        const float lineWidth = ((body.width + body.height) / 2) / 15;
        const Rectangle sourceRec = TextureToSourceRec(texture);
        const float scale = .1f;
        //DrawTextureEx(texture, {body.x, body.y}, 0, scale, color);
        DrawTexturePro(texture,sourceRec,{body.x+body.width/2, body.y+body.height/2, body.width, body.height}, {(float)texture.width*0.05f, (float)texture.height*0.05f}, 0, color);
        if (selected)
        {
            DrawRectangleLinesEx(body, lineWidth, YELLOW);
        }
    }

    float Unit::GetRange() const
    {
        return range;
    }

    Vector2 Unit::GetDestination() const
    {
        return direction;
    }

    bool Unit::IsSelected() const
    {
        return selected;
    }

    void Unit::SetSelected(bool select)
    {
        selected = select;
    }

    Rectangle Unit::GetBody()
    {
        return body;
    }

    Team Unit::GetTeam() const
    {
        return team;
    }

    bool Unit::IsAlive()
    {
        return alive;
    }

    void Unit::SetTarget(Unit* target)
    {
        if (target->GetTeam() != team)
        {
            this->target = target;
        }
    }

    Unit* Unit::GetTarget()
    {
        return target;
    }
}
