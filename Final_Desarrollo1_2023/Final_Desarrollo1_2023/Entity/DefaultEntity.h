#pragma once
#include <raylib.h>

namespace Entity
{
    enum Team
    {
        player,
        enemy,
        neutral
    };
    class DefaultEntity
    {
    public:
        virtual ~DefaultEntity() = default;
        virtual Rectangle GetBody() = 0;
        virtual void DrawBody() = 0;
        Rectangle body{};
    };
}
