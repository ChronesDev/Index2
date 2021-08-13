#pragma once

namespace Index
{
    template<typename T>
    struct alignas(sizeof(T)) Vec1
    {
        T X = 0;
        Vec1() = default;
        Vec1(T x) : X(x) { }
        Vec1<T> operator+(Vec1<T>& other) const { return Vec1<T>(this->X + other.X); }
        Vec1<T> operator-(Vec1<T>& other) const { return Vec1<T>(this->X - other.X); }
        Vec1<T> operator*(Vec1<T>& other) const { return Vec1<T>(this->X * other.X); }
        Vec1<T> operator/(Vec1<T>& other) const { return Vec1<T>(this->X / other.X); }
        Vec1<T>& operator+=(Vec1<T>& other) { this->X += other.X; return *this; }
        Vec1<T>& operator-=(Vec1<T>& other) { this->X -= other.X; return *this; }
        Vec1<T>& operator*=(Vec1<T>& other) { this->X *= other.X; return *this; }
        Vec1<T>& operator/=(Vec1<T>& other) { this->X /= other.X; return *this; }
        Vec1<T> operator+(T other) const { return Vec1<T>(this->X + other); }
        Vec1<T> operator-(T other) const { return Vec1<T>(this->X - other); }
        Vec1<T> operator*(T other) const { return Vec1<T>(this->X * other); }
        Vec1<T> operator/(T other) const { return Vec1<T>(this->X / other); }
        Vec1<T>& operator+=(T other) { this->X += other; return *this; }
        Vec1<T>& operator-=(T other) { this->X -= other; return *this; }
        Vec1<T>& operator*=(T other) { this->X *= other; return *this; }
        Vec1<T>& operator/=(T other) { this->X /= other; return *this; }
        T& operator[](int index) { return ((T*)(this))[index]; }
    };

    template<typename T>
    struct alignas(sizeof(T)) Vec2 : public Vec1<T>
    {
        T Y = 0;
        Vec2() = default;
        Vec2(T x, T y) : Vec1<T>(x), Y(y) { }
        Vec2<T> operator+(Vec2<T>& other) const { return Vec2<T>(this->X + other.X, this->Y + other.Y); }
        Vec2<T> operator-(Vec2<T>& other) const { return Vec2<T>(this->X - other.X, this->Y - other.Y); }
        Vec2<T> operator*(Vec2<T>& other) const { return Vec2<T>(this->X * other.X, this->Y * other.Y); }
        Vec2<T> operator/(Vec2<T>& other) const { return Vec2<T>(this->X / other.X, this->Y / other.Y); }
        Vec2<T>& operator+=(Vec2<T>& other) { this->X += other.X; this->Y += other.Y; return *this; }
        Vec2<T>& operator-=(Vec2<T>& other) { this->X -= other.X; this->Y -= other.Y; return *this; }
        Vec2<T>& operator*=(Vec2<T>& other) { this->X *= other.X; this->Y *= other.Y; return *this; }
        Vec2<T>& operator/=(Vec2<T>& other) { this->X /= other.X; this->Y /= other.Y; return *this; }
        Vec2<T> operator+(T other) const { return Vec2<T>(this->X + other, this->Y + other); }
        Vec2<T> operator-(T other) const { return Vec2<T>(this->X - other, this->Y - other); }
        Vec2<T> operator*(T other) const { return Vec2<T>(this->X * other, this->Y * other); }
        Vec2<T> operator/(T other) const { return Vec2<T>(this->X / other, this->Y / other); }
        Vec2<T>& operator+=(T other) { this->X += other; this->Y += other; return *this; }
        Vec2<T>& operator-=(T other) { this->X -= other; this->Y -= other; return *this; }
        Vec2<T>& operator*=(T other) { this->X *= other; this->Y *= other; return *this; }
        Vec2<T>& operator/=(T other) { this->X /= other; this->Y /= other; return *this; }
        T& operator[](int index) { return ((T*)(this))[index]; }
    };

    template<typename T>
    struct alignas(sizeof(T)) Vec3 : public Vec2<T>
    {
        T Z = 0;
        Vec3() = default;
        Vec3(T x, T y, T z) : Vec2<T>(x, y), Z(z) { }
        Vec3<T> operator+(Vec3<T>& other) const { return Vec3<T>(this->X + other.X, this->Y + other.Y, this->Z + other.Z); }
        Vec3<T> operator-(Vec3<T>& other) const { return Vec3<T>(this->X - other.X, this->Y - other.Y, this->Z - other.Z); }
        Vec3<T> operator*(Vec3<T>& other) const { return Vec3<T>(this->X * other.X, this->Y * other.Y, this->Z * other.Z); }
        Vec3<T> operator/(Vec3<T>& other) const { return Vec3<T>(this->X / other.X, this->Y / other.Y, this->Z / other.Z); }
        Vec3<T>& operator+=(Vec3<T>& other) { this->X += other.X; this->Y += other.Y; this->Z += other.Z; return *this; }
        Vec3<T>& operator-=(Vec3<T>& other) { this->X -= other.X; this->Y -= other.Y; this->Z -= other.Z; return *this; }
        Vec3<T>& operator*=(Vec3<T>& other) { this->X *= other.X; this->Y *= other.Y; this->Z *= other.Z; return *this; }
        Vec3<T>& operator/=(Vec3<T>& other) { this->X /= other.X; this->Y /= other.Y; this->Z /= other.Z; return *this; }
        Vec3<T> operator+(T other) const { return Vec3<T>(this->X + other, this->Y + other, this->Z + other); }
        Vec3<T> operator-(T other) const { return Vec3<T>(this->X - other, this->Y - other, this->Z - other); }
        Vec3<T> operator*(T other) const { return Vec3<T>(this->X * other, this->Y * other, this->Z * other); }
        Vec3<T> operator/(T other) const { return Vec3<T>(this->X / other, this->Y / other, this->Z / other); }
        Vec3<T>& operator+=(T other) { this->X += other; this->Y += other; this->Z += other; return *this; }
        Vec3<T>& operator-=(T other) { this->X -= other; this->Y -= other; this->Z -= other; return *this; }
        Vec3<T>& operator*=(T other) { this->X *= other; this->Y *= other; this->Z *= other; return *this; }
        Vec3<T>& operator/=(T other) { this->X /= other; this->Y /= other; this->Z /= other; return *this; }
        T& operator[](int index) { return ((T*)(this))[index]; }
    };

    template<typename T>
    struct alignas(sizeof(T)) Vec4 : public Vec3<T>
    {
        T W = 0;
        Vec4() = default;
        Vec4(T x, T y, T z, T w) : Vec3<T>(x, y, z), W(w) { }
        Vec4<T> operator+(Vec4<T>& other) const { return Vec4(this->X + other.X, this->Y + other.Y, this->Z + other.Z, this->W + other.W); }
        Vec4<T> operator-(Vec4<T>& other) const { return Vec4(this->X - other.X, this->Y - other.Y, this->Z - other.Z, this->W - other.W); }
        Vec4<T> operator*(Vec4<T>& other) const { return Vec4(this->X * other.X, this->Y * other.Y, this->Z * other.Z, this->W * other.W); }
        Vec4<T> operator/(Vec4<T>& other) const { return Vec4(this->X / other.X, this->Y / other.Y, this->Z / other.Z, this->W / other.W); }
        Vec4<T>& operator+=(Vec4<T>& other) { this->X += other.X; this->Y += other.Y; this->Z += other.Z; this->W += other.W; return *this; }
        Vec4<T>& operator-=(Vec4<T>& other) { this->X -= other.X; this->Y -= other.Y; this->Z -= other.Z; this->W -= other.W; return *this; }
        Vec4<T>& operator*=(Vec4<T>& other) { this->X *= other.X; this->Y *= other.Y; this->Z *= other.Z; this->W *= other.W; return *this; }
        Vec4<T>& operator/=(Vec4<T>& other) { this->X /= other.X; this->Y /= other.Y; this->Z /= other.Z; this->W /= other.W; return *this; }
        Vec4<T> operator+(T other) const { return Vec4<T>(this->X + other, this->Y + other, this->Z + other, this->W + other); }
        Vec4<T> operator-(T other) const { return Vec4<T>(this->X - other, this->Y - other, this->Z - other, this->W - other); }
        Vec4<T> operator*(T other) const { return Vec4<T>(this->X * other, this->Y * other, this->Z * other, this->W * other); }
        Vec4<T> operator/(T other) const { return Vec4<T>(this->X / other, this->Y / other, this->Z / other, this->W / other); }
        Vec4<T>& operator+=(T other) { this->X += other; this->Y += other; this->Z += other; this->W += other; return *this; }
        Vec4<T>& operator-=(T other) { this->X -= other; this->Y -= other; this->Z -= other; this->W -= other; return *this; }
        Vec4<T>& operator*=(T other) { this->X *= other; this->Y *= other; this->Z *= other; this->W *= other; return *this; }
        Vec4<T>& operator/=(T other) { this->X /= other; this->Y /= other; this->Z /= other; this->W /= other; return *this; }
        T& operator[](int index) { return ((T*)(this))[index]; }
    };

    struct Vec1F : public Vec1<float> { using Vec1<float>::Vec1; Vec1F(Vec1<float> v) { static_cast<Vec1<float>&>(*this) = v; } };
    struct Vec2F : public Vec2<float> { using Vec2<float>::Vec2; Vec2F(Vec2<float> v) { static_cast<Vec2<float>&>(*this) = v; } };
    struct Vec3F : public Vec3<float> { using Vec3<float>::Vec3; Vec3F(Vec3<float> v) { static_cast<Vec3<float>&>(*this) = v; } };
    struct Vec4F : public Vec4<float> { using Vec4<float>::Vec4; Vec4F(Vec4<float> v) { static_cast<Vec4<float>&>(*this) = v; } };

    struct Vec1D : public Vec1<double> { using Vec1<double>::Vec1; Vec1D(Vec1<double> v) { static_cast<Vec1<double>&>(*this) = v; } };
    struct Vec2D : public Vec2<double> { using Vec2<double>::Vec2; Vec2D(Vec2<double> v) { static_cast<Vec2<double>&>(*this) = v; } };
    struct Vec3D : public Vec3<double> { using Vec3<double>::Vec3; Vec3D(Vec3<double> v) { static_cast<Vec3<double>&>(*this) = v; } };
    struct Vec4D : public Vec4<double> { using Vec4<double>::Vec4; Vec4D(Vec4<double> v) { static_cast<Vec4<double>&>(*this) = v; } };

    struct Vec1B : public Vec1<__int8> { using Vec1<__int8>::Vec1; Vec1B(Vec1<__int8> v) { static_cast<Vec1<__int8>&>(*this) = v; } };
    struct Vec2B : public Vec2<__int8> { using Vec2<__int8>::Vec2; Vec2B(Vec2<__int8> v) { static_cast<Vec2<__int8>&>(*this) = v; } };
    struct Vec3B : public Vec3<__int8> { using Vec3<__int8>::Vec3; Vec3B(Vec3<__int8> v) { static_cast<Vec3<__int8>&>(*this) = v; } };
    struct Vec4B : public Vec4<__int8> { using Vec4<__int8>::Vec4; Vec4B(Vec4<__int8> v) { static_cast<Vec4<__int8>&>(*this) = v; } };

    struct Vec1S : public Vec1<short> { using Vec1<short>::Vec1; Vec1S(Vec1<short> v) { static_cast<Vec1<short>&>(*this) = v; } };
    struct Vec2S : public Vec2<short> { using Vec2<short>::Vec2; Vec2S(Vec2<short> v) { static_cast<Vec2<short>&>(*this) = v; } };
    struct Vec3S : public Vec3<short> { using Vec3<short>::Vec3; Vec3S(Vec3<short> v) { static_cast<Vec3<short>&>(*this) = v; } };
    struct Vec4S : public Vec4<short> { using Vec4<short>::Vec4; Vec4S(Vec4<short> v) { static_cast<Vec4<short>&>(*this) = v; } };

    struct Vec1I : public Vec1<int> { using Vec1<int>::Vec1; Vec1I(Vec1<int> v) { static_cast<Vec1<int>&>(*this) = v; } };
    struct Vec2I : public Vec2<int> { using Vec2<int>::Vec2; Vec2I(Vec2<int> v) { static_cast<Vec2<int>&>(*this) = v; } };
    struct Vec3I : public Vec3<int> { using Vec3<int>::Vec3; Vec3I(Vec3<int> v) { static_cast<Vec3<int>&>(*this) = v; } };
    struct Vec4I : public Vec4<int> { using Vec4<int>::Vec4; Vec4I(Vec4<int> v) { static_cast<Vec4<int>&>(*this) = v; } };

    struct Vec1L : public Vec1<long long> { using Vec1<long long>::Vec1; Vec1L(Vec1<long long> v) { static_cast<Vec1<long long>&>(*this) = v; } };
    struct Vec2L : public Vec2<long long> { using Vec2<long long>::Vec2; Vec2L(Vec2<long long> v) { static_cast<Vec2<long long>&>(*this) = v; } };
    struct Vec3L : public Vec3<long long> { using Vec3<long long>::Vec3; Vec3L(Vec3<long long> v) { static_cast<Vec3<long long>&>(*this) = v; } };
    struct Vec4L : public Vec4<long long> { using Vec4<long long>::Vec4; Vec4L(Vec4<long long> v) { static_cast<Vec4<long long>&>(*this) = v; } };
}