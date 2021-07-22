#pragma once

#include "../size/size.cc"

namespace Index
{
    struct Rect
    {
        float X = 0, Y = 0, Width = 0, Height = 0;
        Rect() = default;
        Rect(float x, float y, float width, float height) : X(x), Y(y), Width(width), Height(height) { }
        Rect(float x, float y, Size size) : X(x), Y(y), Width(size.Width), Height(size.Height) { }
        Rect(Vec2F vec, float width, float height) : X(vec.X), Y(vec.Y), Width(width), Height(height) { }
        Rect(Vec2F vec, Size size) : X(vec.X), Y(vec.Y), Width(size.Width), Height(size.Height) { }
    };
}