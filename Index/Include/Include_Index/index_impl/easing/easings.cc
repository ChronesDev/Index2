#pragma once

#include <cmath>
#include <numbers>

#include "../core/include.cc"
#include "../helpers/include.cc"
#include "../std/include.cc"

namespace Index::Easings
{
    static constexpr auto PI = std::numbers::pi;

    static double cos(double v) { return ::cos(v); }
    static double sin(double v) { return ::sin(v); }
    static double pow(double v1, double v2) { return ::pow(v1, v2); }
    static double sqrt(double v) { return ::sqrt(v); }

    inline double SineIn(double x) { return 1 - cos((x * PI) / 2); }
    inline double SineOut(double x) { return sin((x * PI) / 2); }
    inline double SineInOut(double x) { return -(cos(PI * x) - 1) / 2; }
    inline double CubicIn(double x) { return x * x * x; }
    inline double CubicOut(double x) { return 1 - pow(1 - x, 3); }
    inline double CubicInOut(double x) { return x < 0.5 ? 4 * x * x * x : 1 - pow(-2 * x + 2, 3) / 2; }
    inline double QuintIn(double x) { return x * x * x * x * x; }
    inline double QuintOut(double x) { return 1 - pow(1 - x, 5); }
    inline double QuintInOut(double x) { return x < 0.5 ? 16 * x * x * x * x * x : 1 - pow(-2 * x + 2, 5) / 2; }
    inline double CircIn(double x) { return 1 - sqrt(1 - pow(x, 2)); }
    inline double CircOut(double x) { return sqrt(1 - pow(x - 1, 2)); }
    inline double CircInOut(double x)
    {
        return x < 0.5 ? (1 - sqrt(1 - pow(2 * x, 2))) / 2 : (sqrt(1 - pow(-2 * x + 2, 2)) + 1) / 2;
    }
    inline double QuadIn(double x) { return x * x; }
    inline double QuadOut(double x) { return 1 - (1 - x) * (1 - x); }
    inline double QuadInOut(double x) { return x < 0.5 ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2; }
    inline double QuartIn(double x) { return x * x * x * x; }
    inline double QuartOut(double x) { return 1 - pow(1 - x, 4); }
    inline double QuartInOut(double x) { return x < 0.5 ? 8 * x * x * x * x : 1 - pow(-2 * x + 2, 4) / 2; }
    inline double ExpoIn(double x) { return x == 0 ? 0 : pow(2, 10 * x - 10); }
    inline double ExpoOut(double x) { return x == 1 ? 1 : 1 - pow(2, -10 * x); }
    inline double ExpoInOut(double x)
    {
        return x == 0 ? 0 : x == 1 ? 1 : x < 0.5 ? pow(2, 20 * x - 10) / 2 : (2 - pow(2, -20 * x + 10)) / 2;
    }

}