#pragma once

#include "../vector/vector.cc"

namespace Index
{
    struct Color
    {
        struct RawColor { float RawR = 0, RawG = 0, RawB = 0, RawA = 1; };
        float R = 0, G = 0, B = 0, A = 1;
        Color() = default;
        Color(int r, int g, int b, int a = 255) {
            R = r != 0 ? (float)r / 255.0f : 0;
            G = g != 0 ? (float)g / 255.0f : 0;
            B = b != 0 ? (float)b / 255.0f : 0;
            A = a != 0 ? (float)a / 255.0f : 0;
        }
        explicit Color(RawColor rawColor) { R = rawColor.RawR; G = rawColor.RawG; B = rawColor.RawB; A = rawColor.RawA; }
        bool operator==(const Color& other) const = default;
        bool operator!=(const Color& other) const = default;
        Vec4F AsVec() const { return Vec4F { R * 255.0f, G * 255.0f, B * 255.0f, A * 255.0f }; };
        Vec4F AsRawVec() const { return Vec4F { R, G, B, A }; }
        static Color RGB(Vec3F rgb) { return Color(rgb.X, rgb.Y, rgb.Z); }
        static Color RGB(Vec3I rgb) { return Color(rgb.X, rgb.Y, rgb.Z); }
        static Color RGB(int r, int g, int b) { return Color(r, g, b); }
        static Color RGB(unsigned int rgb) {
            return Color(
                (rgb & 0xFF0000) >> 16,
                (rgb & 0xFF00) >> 8,
                (rgb & 0xFF)
            );
        }
        static Color RGBA(Vec4F rgba) { return Color(rgba.X, rgba.Y, rgba.Z, rgba.W); }
        static Color RGBA(int r, int g, int b, int a = 255) { return Color(r, g, b, a); }
        static Color RGBA(unsigned int rgba) {
            return Color(
                (rgba & 0xFF000000) >> 24,
                (rgba & 0xFF0000) >> 16,
                (rgba & 0xFF00) >> 8,
                (rgba & 0xFF)
            );
        }
        static Color ARGB(Vec4F argb) { return Color(argb.Y, argb.X, argb.W, argb.X); }
        static Color ARGB(int r, int g, int b, int a = 255) { return Color(r, g, b, a); }
        static Color ARGB(unsigned int argb) {
            return Color(
                (argb & 0xFF0000) >> 16,
                (argb & 0xFF00) >> 8,
                (argb & 0xFF),
                (argb & 0xFF000000) >> 24
            );
        }
        static Color Raw(Vec3F raw) { return Color(RawColor{ .RawR = raw.X, .RawG = raw.Y, .RawB = raw.Z }); }
        static Color Raw(Vec4F raw) { return Color(RawColor{ .RawR = raw.X, .RawG = raw.Y, .RawB = raw.Z, .RawA = raw.W }); }
    };
}