#pragma once

#include <cmath>
#include <numbers>

#include "../core/include.cc"
#include "../helpers/include.cc"
#include "../std/include.cc"

namespace Index::Easing
{
    constexpr auto PI = std::numbers::pi;

    inline double cos(double v) { return ::cos(v); }
    inline double sin(double v) { return ::sin(v); }
    inline double pow(double v1, double v2) { return ::pow(v1, v2); }
    inline double sqrt(double v) { return ::sqrt(v); }

    inline double EaseInSine(double x) { return 1 - cos((x * PI) / 2); }
    inline double EaseOutSine(double x) { return sin((x * PI) / 2); }
    inline double EaseInOutSine(double x) { return -(cos(PI * x) - 1) / 2; }
    inline double EaseInCubic(double x) { return x * x * x; }
    inline double EaseOutCubic(double x) { return 1 - pow(1 - x, 3); }
    inline double EaseInOutCubic(double x) { return x < 0.5 ? 4 * x * x * x : 1 - pow(-2 * x + 2, 3) / 2; }
    inline double EaseInQuint(double x) { return x * x * x * x * x; }
    inline double EaseOutQuint(double x) { return 1 - pow(1 - x, 5); }
    inline double EaseInOutQuint(double x) { return x < 0.5 ? 16 * x * x * x * x * x : 1 - pow(-2 * x + 2, 5) / 2; }
    inline double EaseInCirc(double x) { return 1 - sqrt(1 - pow(x, 2)); }
    inline double EaseOutCirc(double x) { return sqrt(1 - pow(x - 1, 2)); }
    inline double EaseInOutCirc(double x)
    {
        return x < 0.5 ? (1 - sqrt(1 - pow(2 * x, 2))) / 2 : (sqrt(1 - pow(-2 * x + 2, 2)) + 1) / 2;
    }
    inline double EaseInQuad(double x) { return x * x; }
    inline double EaseOutQuad(double x) { return 1 - (1 - x) * (1 - x); }
    inline double EaseInOutQuad(double x) { return x < 0.5 ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2; }
    inline double EaseInQuart(double x) { return x * x * x * x; }
    inline double EaseOutQuart(double x) { return 1 - pow(1 - x, 4); }
    inline double EaseInOutQuart(double x) { return x < 0.5 ? 8 * x * x * x * x : 1 - pow(-2 * x + 2, 4) / 2; }
    inline double EaseInExpo(double x) { return x == 0 ? 0 : pow(2, 10 * x - 10); }
    inline double EaseOutExpo(double x) { return x == 1 ? 1 : 1 - pow(2, -10 * x); }
    inline double EaseInOutExpo(double x)
    {
        return x == 0 ? 0 : x == 1 ? 1 : x < 0.5 ? pow(2, 20 * x - 10) / 2 : (2 - pow(2, -20 * x + 10)) / 2;
    }

}