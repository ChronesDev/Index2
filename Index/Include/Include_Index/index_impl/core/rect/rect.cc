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
        [[nodiscard]] Size GetSize() const {
            return { Width, Height };
        }
        void SetSize(Size size) {
            Width = size.Width; Height = size.Height;
        }
        __declspec(property(get = GetSize, put = SetSize)) Size Size;
        [[nodiscard]] Vec2F GetFirstPoint() const {
            return { X, Y };
        }
        [[nodiscard]] Vec2F GetSecondPoint() const {
            return { X + Width, Y + Height };
        }
        [[nodiscard]] Vec2F GetCenter() const {
            return { X + (Width / 2), Y + (Height / 2) };
        }
        __declspec(property(get = GetFirstPoint)) Vec2F First;
        __declspec(property(get = GetSecondPoint)) Vec2F Second;
        __declspec(property(get = GetCenter)) Vec2F Center;
    };
}