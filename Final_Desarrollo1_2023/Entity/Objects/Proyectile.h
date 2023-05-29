#pragma once
#include "../Entity.h"

namespace Objects
{
    class Proyectile : public Entity::Entity
    {
    public:
        Proyectile();

    private:
        float speed;
        float damage;
        //float
    };
}
