#pragma once

#include <algorithm>
#include <cmath>

namespace Index
{
    template<class T> inline constexpr T Min(T a, T b) {
        return a < b ? a : b;
    }

    template<class T> inline constexpr T Max(T a, T b) {
        return a > b ? a : b;
    }

    template<class T> inline constexpr T Clamp(T v, T a, T b) {
        std::clamp(v, a, b);
    }

    template<class T> inline constexpr T Lerp(T a, T b, T v) {
        std::lerp(a, b, v);
    }
}