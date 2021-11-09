#pragma once

#include <cmath>
#include <numbers>

#include "../core/include.cc"
#include "../helpers/include.cc"
#include "../std/include.cc"

namespace Index::Easing
{
    constexpr auto PI = std::numbers::pi;

    double cos(double v) { return ::cos(v); }
    double sin(double v) { return ::sin(v); }
    double pow(double v1, double v2) { return ::pow(v1, v2); }
    double sqrt(double v) { return ::sqrt(v); }

    double EaseInSine(double x) { return 1 - cos((x * PI) / 2); }
    double EaseOutSine(double x) { return sin((x * PI) / 2); }
    double EaseInOutSine(double x) { return -(cos(PI * x) - 1) / 2; }
    double EaseInCubic(double x) { return x * x * x; }
    double EaseOutCubic(double x) { return 1 - pow(1 - x, 3); }
    double EaseInOutCubic(double x) { return x < 0.5 ? 4 * x * x * x : 1 - pow(-2 * x + 2, 3) / 2; }
    double EaseInQuint(double x) { return x * x * x * x * x; }
    double EaseOutQuint(double x) { return 1 - pow(1 - x, 5); }
    double EaseInOutQuint(double x) { return x < 0.5 ? 16 * x * x * x * x * x : 1 - pow(-2 * x + 2, 5) / 2; }
    double EaseInCirc(double x) { return 1 - sqrt(1 - pow(x, 2)); }
    double EaseOutCirc(double x) { return sqrt(1 - pow(x - 1, 2)); }
    double EaseInOutCirc(double x)
    {
        return x < 0.5 ? (1 - sqrt(1 - pow(2 * x, 2))) / 2 : (sqrt(1 - pow(-2 * x + 2, 2)) + 1) / 2;
    }
    double EaseInQuad(double x) { return x * x; }
    double EaseOutQuad(double x) { return 1 - (1 - x) * (1 - x); }
    double EaseInOutQuad(double x) { return x < 0.5 ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2; }
    double EaseInQuart(double x) { return x * x * x * x; }
    double EaseOutQuart(double x) { return 1 - pow(1 - x, 4); }
    double EaseInOutQuart(double x) { return x < 0.5 ? 8 * x * x * x * x : 1 - pow(-2 * x + 2, 4) / 2; }
    double EaseInExpo(double x) { return x == 0 ? 0 : pow(2, 10 * x - 10); }
    double EaseOutExpo(double x) { return x == 1 ? 1 : 1 - pow(2, -10 * x); }
    double EaseInOutExpo(double x)
    {
        return x == 0 ? 0 : x == 1 ? 1 : x < 0.5 ? pow(2, 20 * x - 10) / 2 : (2 - pow(2, -20 * x + 10)) / 2;
    }

}