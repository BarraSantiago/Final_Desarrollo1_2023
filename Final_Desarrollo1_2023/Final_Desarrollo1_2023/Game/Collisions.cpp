#include "Collisions.h"

bool Collision::AABBCollision(Entity::DefaultEntity* a, Entity::DefaultEntity* b)
{
    return (a->body.x < b->body.x + b->body.width &&
    a->body.x + a->body.width > b->body.x &&
    a->body.y < b->body.y + b->body.height &&
    a->body.y + a->body.height > b->body.y);
}
