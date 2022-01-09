#pragma once

#include "../vector/vector.cc"

namespace Index
{
    struct Size
    {
        float Width = 0, Height = 0;

        constexpr Size() = default;
        constexpr Size(float width, float height)
            : Width(width)
            , Height(height)
        {
        }
        constexpr Size(Vec2F vec)
            : Width(vec.X)
            , Height(vec.Y)
        {
        }

        bool operator==(const Size& other) const = default;
        bool operator!=(const Size& other) const = default;
        operator Vec2F() const { return { Width, Height }; }
    };
}