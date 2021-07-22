#pragma once

#include "../vector/vector.cc"

namespace Index
{
    struct Size
    {
        float Width = 0, Height = 0;
        Size() = default;
        Size(float width, float height) : Width(width), Height(height) { }
        Size(Vec2F vec) : Width(vec.X), Height(vec.Y) { }
    };
}