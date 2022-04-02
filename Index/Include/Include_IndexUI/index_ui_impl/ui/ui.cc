#pragma once

#include "../index.cc"

// Prototypes
namespace Index::UI
{
    struct UIMapper;
    struct UIElement;
    struct UIFrameCounter;
}

// Variables
namespace Index::UI
{
    constexpr float AutoF = Limits::FloatMax;
    constexpr Size AutoS = { AutoF, AutoF };
}

// Math
namespace Index::UI
{
    inline Size Min_(Size a, Size b) { return { Min(a.Width, a.Width), Min(a.Height, a.Height) }; }
    inline Size Max_(Size a, Size b) { return { Max(a.Width, a.Width), Max(a.Height, a.Height) }; }

    inline Vec2F Min_(Vec2F a, Vec2F b) { return { Min(a.X, a.X), Min(a.Y, a.Y) }; }
    inline Vec2F Max_(Vec2F a, Vec2F b) { return { Max(a.X, a.X), Max(a.Y, a.Y) }; }

    inline Vec3F Min_(Vec3F a, Vec3F b) { return { Min(a.X, a.X), Min(a.Y, a.Y), Min(a.Z, b.Z) }; }
    inline Vec3F Max_(Vec3F a, Vec3F b) { return { Max(a.X, a.X), Max(a.Y, a.Y), Max(a.Z, b.Z) }; }

    inline float AutoF_ValueOr_(float a, float x)
    {
        if (a == AutoF)
            return x;
        else
            return a;
    }
}

// UIFrameCounter
namespace Index::UI
{
    struct UIFrameCounter
    {
        ulong Frame = 0;

        ulong Next()
        {
            Frame = (Frame % (Limits::MaxValueOf<ulong>() - 1)) + 1;
            return Frame;
        }

        ulong Begin()
        {
            Frame = 0;
            return Frame;
        }

        operator ulong() { return Frame; }
    };
}