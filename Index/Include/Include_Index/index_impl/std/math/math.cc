#pragma once

#include <algorithm>
#include <cmath>

namespace Index
{
    template <class T> inline constexpr T Min(T a, T b) { return a < b ? a : b; }

    template <class T> inline constexpr T Max(T a, T b) { return a > b ? a : b; }

    template <class T> inline constexpr T Clamp(T v, T a, T b) { return std::clamp(v, a, b); }

    template <class T> inline constexpr T Lerp(T a, T b, T v) { return std::lerp(a, b, v); }

    template <class T> inline constexpr T LerpClamp(T a, T b, T v) { return Clamp(Lerp(a, b, v), a, b); }

    template <class T> inline constexpr T LerpC(T a, T b, T v) { return LerpClamp(a, b, v); }

    template <class T> inline constexpr T Limit(T v, T a, T b)
    {
        if (a > b)
            return Clamp(v, b, a);
        else
            return Clamp(v, a, b);
    }

    template <class T> inline constexpr T LerpLimit(T a, T b, T v) { return Limit(Lerp(a, b, v), a, b); }

    template <class T> inline constexpr T LerpL(T a, T b, T v) { return LerpLimit(a, b, v); }
}