#pragma once

#include <algorithm>
#include <cmath>

namespace Index
{
    template <class T> inline constexpr T Min(T a, T b) { return a < b ? a : b; }

    template <class T> inline constexpr T Max(T a, T b) { return a > b ? a : b; }

    template <class T> inline constexpr T Clamp(T v, T a, T b) { return std::clamp(v, a, b); }

    template <class T> inline constexpr T Lerp(T a, T b, T v) { return std::lerp(a, b, v); }

    template <class T> inline constexpr T LerpClamp(T a, T b, T v) { return Clamp(std::lerp(a, b, v), a, b); }
}