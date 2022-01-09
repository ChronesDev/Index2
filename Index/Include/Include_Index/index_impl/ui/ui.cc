#pragma once

#include <utility>
#include <variant>

#include "../core/include.cc"
#include "../helpers/include.cc"
#include "../std/include.cc"

// ##################################### //
#pragma region Declaration
// ##################################### //

// Prototypes
namespace Index::UI
{
    struct UINotification;
    struct Layout;
    struct UIElementLayoutCache;
    struct UIElement;
    struct UIElementHolder;
    struct UIAnimation;
    struct UIDynamic;
    struct UIContext;
}

// Important
namespace Index
{
    __forceinline Vec2F Min(Vec2F v1, Vec2F v2);

    __forceinline Vec2F Max(Vec2F v1, Vec2F v2);

    __forceinline Size Min(Size v1, Size v2);

    __forceinline Size Max(Size v1, Size v2);
}

// Important
namespace Index::UI
{
    // NullF: The Float value that represents Null
    constexpr float NullF = Limits::FloatMax;

    __forceinline float Validate(float v1, float $else);

    __forceinline float Validate2(float v1, float v2, float $else);

    __forceinline float Validate3(float v1, float v2, float v3, float $else);

    __forceinline Vec2F Validate(Vec2F v1, Vec2F $else);

    __forceinline Vec2F Validate2(Vec2F v1, Vec2F v2, Vec2F $else);

    __forceinline Vec2F Validate3(Vec2F v1, Vec2F v2, Vec2F v3, Vec2F $else);

    __forceinline Size Validate(Size v1, Size $else);

    __forceinline Size Validate2(Size v1, Size v2, Size $else);

    __forceinline Size Validate3(Size v1, Size v2, Size v3, Size $else);

    __forceinline Size GetMinSize(UIElement* e);

    __forceinline Size GetMaxSize(UIElement* e);

    __forceinline Rect AlignRect(Rect box, Size content, Align align);

    __forceinline Rect AlignRectNoStretch(Rect box, Size content, Align align);

    __forceinline Rect AlignRectWithMaxSize(Rect box, Size content, Size maxSize, Align align);

    __forceinline Rect GetSubrect(UIElement* e, Layout i);

    __forceinline Rect GetSubrectWithCustomIntentSize(UIElement* e, Layout i, Size intentSize);

    __forceinline Size GetIntentSizeFrom(Layout i, List<IPtr<UIElement>>& content);
}

// Dynamic
namespace Index::UI
{
    // DynamicSizeCache
    template <typename T> struct DynamicVec1Cache : Vec1<T>
    {
        using Vec1<T>::Vec1;
    };

    // DynamicSizeCache
    template <typename T> struct DynamicVec2Cache : Vec2<T>
    {
        using Vec2<T>::Vec2;
    };

    // DynamicSizeCache
    template <typename T> struct DynamicVec3Cache : Vec3<T>
    {
        using Vec3<T>::Vec3;
    };

    // DynamicSizeCache
    template <typename T> struct DynamicVec4Cache : Vec4<T>
    {
        using Vec4<T>::Vec4;
    };

    // DynamicSizeCache
    struct DynamicSizeCache : Size
    {
        using Size::Size;
    };

    // DynamicSizeCache
    struct DynamicRectCache : Rect
    {
        using Rect::Rect;
    };

    // DynamicVec1
    template <typename T> struct DynamicVec1
    {
        using DynamicFunc = Func<float()>;
        using DynamicFuncThis = Func<float(DynamicVec1& self)>;
        using DynamicVar = Variant<float, int, DynamicFunc, DynamicFuncThis>;
        DynamicVec1Cache<T> Cache {};
        DynamicVar X;

        DynamicVec1() = default;

        DynamicVec1(DynamicVar x)
            : X(x)
        {
        }

        DynamicVec1(Vec1F vec)
            : X(vec.X)
        {
        }

        DynamicVec1Cache<T> GetCache()
        {
            DynamicVec1Cache<T> cache;
            if (X.template Has<float>()) { cache.X = X.template Get<float>(); }
            else if (X.template Has<int>())
            {
                cache.X = X.template Get<int>();
            }
            else if (X.template Has<DynamicFunc>())
            {
                auto& func = X.template Get<DynamicFunc>();
                if (func)
                    cache.X = func();
                else
                    cache.X = DefaultOf<float>();
            }
            else if (X.template Has<DynamicFuncThis>())
            {
                auto& func = X.template Get<DynamicFuncThis>();
                if (func)
                    cache.X = func(*this);
                else
                    cache.X = DefaultOf<float>();
            }
            return cache;
        }

        void CacheContent() { Cache = GetCache(); }

        bool operator==(DynamicVec1<T>& rhs) { return GetCache() == rhs.GetCache(); }

        bool operator!=(DynamicVec1<T>& rhs) { return rhs != *this; }
    };

    // DynamicVec2
    template <typename T> struct DynamicVec2
    {
        using DynamicFunc = Func<float()>;
        using DynamicFuncThis = Func<float(DynamicVec2& self)>;
        using DynamicVar = Variant<float, int, DynamicFunc, DynamicFuncThis>;
        DynamicVec2Cache<T> Cache {};
        DynamicVar X, Y;

        DynamicVec2() = default;

        DynamicVec2(DynamicVar x, DynamicVar y)
            : X(x)
            , Y(y)
        {
        }

        DynamicVec2(Vec2F vec)
            : X(vec.X)
            , Y(vec.Y)
        {
        }

        DynamicVec2Cache<T> GetCache()
        {
            DynamicVec2Cache<T> cache;
            if (X.template Has<float>()) { cache.X = X.template Get<float>(); }
            else if (X.template Has<int>())
            {
                cache.X = X.template Get<int>();
            }
            else if (X.template Has<DynamicFunc>())
            {
                auto& func = X.template Get<DynamicFunc>();
                if (func)
                    cache.X = func();
                else
                    cache.X = DefaultOf<float>();
            }
            else if (X.template Has<DynamicFuncThis>())
            {
                auto& func = X.template Get<DynamicFuncThis>();
                if (func)
                    cache.X = func(*this);
                else
                    cache.X = DefaultOf<float>();
            }
            if (Y.template Has<float>()) { cache.Y = Y.template Get<float>(); }
            else if (Y.template Has<int>())
            {
                cache.Y = Y.template Get<int>();
            }
            else if (Y.template Has<DynamicFunc>())
            {
                auto& func = Y.template Get<DynamicFunc>();
                if (func)
                    cache.Y = func();
                else
                    cache.Y = DefaultOf<float>();
            }
            else if (Y.template Has<DynamicFuncThis>())
            {
                auto& func = Y.template Get<DynamicFuncThis>();
                if (func)
                    cache.Y = func(*this);
                else
                    cache.Y = DefaultOf<float>();
            }
            return cache;
        }

        void CacheContent() { Cache = GetCache(); }

        bool operator==(DynamicVec2<T>& rhs) { return GetCache() == rhs.GetCache(); }

        bool operator!=(DynamicVec2<T>& rhs) { return rhs != *this; }
    };

    // DynamicVec3
    template <typename T> struct DynamicVec3
    {
        using DynamicFunc = Func<float()>;
        using DynamicFuncThis = Func<float(DynamicVec3& self)>;
        using DynamicVar = Variant<float, int, DynamicFunc, DynamicFuncThis>;
        DynamicVec3Cache<T> Cache {};
        DynamicVar X, Y, Z;

        DynamicVec3() = default;

        DynamicVec3(DynamicVar x, DynamicVar y, DynamicVar z)
            : X(x)
            , Y(y)
            , Z(z)
        {
        }

        DynamicVec3(Vec3F vec)
            : X(vec.X)
            , Y(vec.Y)
            , Z(vec.Z)
        {
        }

        DynamicVec3Cache<T> GetCache()
        {
            DynamicVec3Cache<T> cache;
            if (X.template Has<float>()) { cache.X = X.template Get<float>(); }
            else if (X.template Has<int>())
            {
                cache.X = X.template Get<int>();
            }
            else if (X.template Has<DynamicFunc>())
            {
                auto& func = X.template Get<DynamicFunc>();
                if (func)
                    cache.X = func();
                else
                    cache.X = DefaultOf<float>();
            }
            else if (X.template Has<DynamicFuncThis>())
            {
                auto& func = X.template Get<DynamicFuncThis>();
                if (func)
                    cache.X = func(*this);
                else
                    cache.X = DefaultOf<float>();
            }
            if (Y.template Has<float>()) { cache.Y = Y.template Get<float>(); }
            else if (Y.template Has<int>())
            {
                cache.Y = Y.template Get<int>();
            }
            else if (Y.template Has<DynamicFunc>())
            {
                auto& func = Y.template Get<DynamicFunc>();
                if (func)
                    cache.Y = func();
                else
                    cache.Y = DefaultOf<float>();
            }
            else if (Y.template Has<DynamicFuncThis>())
            {
                auto& func = Y.template Get<DynamicFuncThis>();
                if (func)
                    cache.Y = func(*this);
                else
                    cache.Y = DefaultOf<float>();
            }
            if (Z.template Has<float>()) { cache.Z = Z.template Get<float>(); }
            else if (Z.template Has<int>())
            {
                cache.Z = Z.template Get<int>();
            }
            else if (Z.template Has<DynamicFunc>())
            {
                auto& func = Z.template Get<DynamicFunc>();
                if (func)
                    cache.Z = func();
                else
                    cache.Z = DefaultOf<float>();
            }
            else if (Z.template Has<DynamicFuncThis>())
            {
                auto& func = Z.template Get<DynamicFuncThis>();
                if (func)
                    cache.Z = func(*this);
                else
                    cache.Z = DefaultOf<float>();
            }
            return cache;
        }

        void CacheContent() { Cache = GetCache(); }

        bool operator==(DynamicVec3<T>& rhs) { return GetCache() == rhs.GetCache(); }

        bool operator!=(DynamicVec3<T>& rhs) { return rhs != *this; }
    };

    // DynamicVec4
    template <typename T> struct DynamicVec4
    {
        using DynamicFunc = Func<float()>;
        using DynamicFuncThis = Func<float(DynamicVec4& self)>;
        using DynamicVar = Variant<float, int, DynamicFunc, DynamicFuncThis>;
        DynamicVec4Cache<T> Cache {};
        DynamicVar X, Y, Z, W;

        DynamicVec4() = default;

        DynamicVec4(DynamicVar x, DynamicVar y, DynamicVar z, DynamicVar w)
            : X(x)
            , Y(y)
            , Z(z)
            , W(w)
        {
        }

        DynamicVec4(Vec4F vec)
            : X(vec.X)
            , Y(vec.Y)
            , Z(vec.Z)
            , W(vec.W)
        {
        }

        DynamicVec4Cache<T> GetCache()
        {
            DynamicVec4Cache<T> cache;
            if (X.template Has<float>()) { cache.X = X.template Get<float>(); }
            else if (X.template Has<int>())
            {
                cache.X = X.template Get<int>();
            }
            else if (X.template Has<DynamicFunc>())
            {
                auto& func = X.template Get<DynamicFunc>();
                if (func)
                    cache.X = func();
                else
                    cache.X = DefaultOf<float>();
            }
            else if (X.template Has<DynamicFuncThis>())
            {
                auto& func = X.template Get<DynamicFuncThis>();
                if (func)
                    cache.X = func(*this);
                else
                    cache.X = DefaultOf<float>();
            }
            if (Y.template Has<float>()) { cache.Y = Y.template Get<float>(); }
            else if (Y.template Has<int>())
            {
                cache.Y = Y.template Get<int>();
            }
            else if (Y.template Has<DynamicFunc>())
            {
                auto& func = Y.template Get<DynamicFunc>();
                if (func)
                    cache.Y = func();
                else
                    cache.Y = DefaultOf<float>();
            }
            else if (Y.template Has<DynamicFuncThis>())
            {
                auto& func = Y.template Get<DynamicFuncThis>();
                if (func)
                    cache.Y = func(*this);
                else
                    cache.Y = DefaultOf<float>();
            }
            if (Z.template Has<float>()) { cache.Z = Z.template Get<float>(); }
            else if (Z.template Has<int>())
            {
                cache.Z = Z.template Get<int>();
            }
            else if (Z.template Has<DynamicFunc>())
            {
                auto& func = Z.template Get<DynamicFunc>();
                if (func)
                    cache.Z = func();
                else
                    cache.Z = DefaultOf<float>();
            }
            else if (Z.template Has<DynamicFuncThis>())
            {
                auto& func = Z.template Get<DynamicFuncThis>();
                if (func)
                    cache.Z = func(*this);
                else
                    cache.Z = DefaultOf<float>();
            }
            if (W.template Has<float>()) { cache.W = W.template Get<float>(); }
            else if (W.template Has<int>())
            {
                cache.W = W.template Get<int>();
            }
            else if (W.template Has<DynamicFunc>())
            {
                auto& func = W.template Get<DynamicFunc>();
                if (func)
                    cache.W = func();
                else
                    cache.W = DefaultOf<float>();
            }
            else if (W.template Has<DynamicFuncThis>())
            {
                auto& func = W.template Get<DynamicFuncThis>();
                if (func)
                    cache.W = func(*this);
                else
                    cache.W = DefaultOf<float>();
            }
            return cache;
        }

        void CacheContent() { Cache = GetCache(); }

        bool operator==(DynamicVec4<T>& rhs) { return GetCache() == rhs.GetCache(); }

        bool operator!=(DynamicVec4<T>& rhs) { return rhs != *this; }
    };

    using DynamicVec1F = DynamicVec1<float>;
    using DynamicVec2F = DynamicVec2<float>;
    using DynamicVec3F = DynamicVec3<float>;
    using DynamicVec4F = DynamicVec4<float>;

    using DynamicVec1D = DynamicVec1<double>;
    using DynamicVec2D = DynamicVec2<double>;
    using DynamicVec3D = DynamicVec3<double>;
    using DynamicVec4D = DynamicVec4<double>;

    using DynamicVec1B = DynamicVec1<__int8>;
    using DynamicVec2B = DynamicVec2<__int8>;
    using DynamicVec3B = DynamicVec3<__int8>;
    using DynamicVec4B = DynamicVec4<__int8>;

    using DynamicVec1S = DynamicVec1<short>;
    using DynamicVec2S = DynamicVec2<short>;
    using DynamicVec3S = DynamicVec3<short>;
    using DynamicVec4S = DynamicVec4<short>;

    using DynamicVec1I = DynamicVec1<int>;
    using DynamicVec2I = DynamicVec2<int>;
    using DynamicVec3I = DynamicVec3<int>;
    using DynamicVec4I = DynamicVec4<int>;

    using DynamicVec1L = DynamicVec1<long long>;
    using DynamicVec2L = DynamicVec2<long long>;
    using DynamicVec3L = DynamicVec3<long long>;
    using DynamicVec4L = DynamicVec4<long long>;

    // DynamicSize
    struct DynamicSize
    {
        using DynamicFunc = Func<float()>;
        using DynamicFuncThis = Func<float(DynamicSize& self)>;
        using DynamicVar = Variant<float, int, DynamicFunc, DynamicFuncThis>;
        DynamicSizeCache Cache {};
        DynamicVar Width, Height;

        DynamicSize() = default;

        DynamicSize(DynamicVar width, DynamicVar height)
            : Width(width)
            , Height(height)
        {
        }

        DynamicSize(Vec2F vec)
            : Width(vec.X)
            , Height(vec.Y)
        {
        }

        DynamicSizeCache GetCache()
        {
            DynamicSizeCache cache;
            if (Width.Has<float>()) { cache.Width = Width.Get<float>(); }
            if (Width.Has<int>()) { cache.Width = Width.Get<int>(); }
            else if (Width.Has<DynamicFunc>())
            {
                auto& func = Width.Get<DynamicFunc>();
                if (func)
                    cache.Width = func();
                else
                    cache.Width = DefaultOf<float>();
            }
            else if (Width.Has<DynamicFuncThis>())
            {
                auto& func = Width.Get<DynamicFuncThis>();
                if (func)
                    cache.Width = func(*this);
                else
                    cache.Width = DefaultOf<float>();
            }
            if (Height.Has<float>()) { cache.Height = Height.Get<float>(); }
            if (Height.Has<int>()) { cache.Height = Height.Get<int>(); }
            else if (Height.Has<DynamicFunc>())
            {
                auto& func = Height.Get<DynamicFunc>();
                if (func)
                    cache.Height = func();
                else
                    cache.Height = DefaultOf<float>();
            }
            else if (Height.Has<DynamicFuncThis>())
            {
                auto& func = Height.Get<DynamicFuncThis>();
                if (func)
                    cache.Height = func(*this);
                else
                    cache.Height = DefaultOf<float>();
            }
            return cache;
        }

        void CacheContent() { Cache = GetCache(); }

        bool operator==(DynamicSize& rhs) { return GetCache() == rhs.GetCache(); }

        bool operator!=(DynamicSize& rhs) { return !(rhs == *this); }
    };

    // DynamicRect
    struct DynamicRect
    {
        using DynamicFunc = Func<float()>;
        using DynamicFuncThis = Func<float(DynamicRect& self)>;
        using DynamicVar = Variant<float, int, DynamicFunc, DynamicFuncThis>;
        DynamicRectCache Cache {};
        DynamicVar X, Y;
        DynamicVar Width, Height;

        DynamicRect() = default;

        DynamicRect(DynamicVar x, DynamicVar y, DynamicVar width, DynamicVar height)
            : X(x)
            , Y(y)
            , Width(width)
            , Height(height)
        {
        }

        DynamicRect(Vec4F vec)
            : X(vec.X)
            , Y(vec.Y)
            , Width(vec.Z)
            , Height(vec.W)
        {
        }

        DynamicRect(Rect rect)
            : X(rect.X)
            , Y(rect.Y)
            , Width(rect.Width)
            , Height(rect.Height)
        {
        }

        DynamicRectCache GetCache()
        {
            DynamicRectCache cache;
            if (X.template Has<float>()) { cache.X = X.template Get<float>(); }
            else if (X.template Has<int>())
            {
                cache.X = X.template Get<int>();
            }
            else if (X.template Has<DynamicFunc>())
            {
                auto& func = X.template Get<DynamicFunc>();
                if (func)
                    cache.X = func();
                else
                    cache.X = DefaultOf<float>();
            }
            else if (X.template Has<DynamicFuncThis>())
            {
                auto& func = X.template Get<DynamicFuncThis>();
                if (func)
                    cache.X = func(*this);
                else
                    cache.X = DefaultOf<float>();
            }
            if (Y.template Has<float>()) { cache.Y = Y.template Get<float>(); }
            else if (Y.template Has<int>())
            {
                cache.Y = Y.template Get<int>();
            }
            else if (Y.template Has<DynamicFunc>())
            {
                auto& func = Y.template Get<DynamicFunc>();
                if (func)
                    cache.Y = func();
                else
                    cache.Y = DefaultOf<float>();
            }
            else if (Y.template Has<DynamicFuncThis>())
            {
                auto& func = Y.template Get<DynamicFuncThis>();
                if (func)
                    cache.Y = func(*this);
                else
                    cache.Y = DefaultOf<float>();
            }
            if (Width.Has<float>()) { cache.Width = Width.Get<float>(); }
            if (Width.Has<int>()) { cache.Width = Width.Get<int>(); }
            else if (Width.Has<DynamicFunc>())
            {
                auto& func = Width.Get<DynamicFunc>();
                if (func)
                    cache.Width = func();
                else
                    cache.Width = DefaultOf<float>();
            }
            else if (Width.Has<DynamicFuncThis>())
            {
                auto& func = Width.Get<DynamicFuncThis>();
                if (func)
                    cache.Width = func(*this);
                else
                    cache.Width = DefaultOf<float>();
            }
            if (Height.Has<float>()) { cache.Height = Height.Get<float>(); }
            if (Height.Has<int>()) { cache.Height = Height.Get<int>(); }
            else if (Height.Has<DynamicFunc>())
            {
                auto& func = Height.Get<DynamicFunc>();
                if (func)
                    cache.Height = func();
                else
                    cache.Height = DefaultOf<float>();
            }
            else if (Height.Has<DynamicFuncThis>())
            {
                auto& func = Height.Get<DynamicFuncThis>();
                if (func)
                    cache.Height = func(*this);
                else
                    cache.Height = DefaultOf<float>();
            }
            return cache;
        }

        void CacheContent() { Cache = GetCache(); }

        bool operator==(DynamicRect& rhs) { return GetCache() == rhs.GetCache(); }

        bool operator!=(DynamicRect& rhs) { return !(rhs == *this); }
    };
}

// Dyn
namespace Index::UI
{
#define INDEX_UI_DynSize_Constructor_All_FirstType_SecondType(t1, t2)                                                 \
    DynSize(t1 width, t1 height)                                                                                      \
        : _Width(width)                                                                                               \
        , _Height(height)                                                                                             \
    {                                                                                                                 \
    }                                                                                                                 \
    DynSize(t2 width, t2 height)                                                                                      \
        : _Width(width)                                                                                               \
        , _Height(height)                                                                                             \
    {                                                                                                                 \
    }                                                                                                                 \
    DynSize(t1 width, t2 height)                                                                                      \
        : _Width(width)                                                                                               \
        , _Height(height)                                                                                             \
    {                                                                                                                 \
    }                                                                                                                 \
    DynSize(t2 width, t1 height)                                                                                      \
        : _Width(width)                                                                                               \
        , _Height(height)                                                                                             \
    {                                                                                                                 \
    }

#define INDEX_UI_DynSize_Constructor_All_Cast_FirstType_SecondType(t1, t2, t1Cast, t2Cast)                            \
    DynSize(t1 width, t1 height)                                                                                      \
        : _Width((t1Cast)width)                                                                                       \
        , _Height((t1Cast)height)                                                                                     \
    {                                                                                                                 \
    }                                                                                                                 \
    DynSize(t2 width, t2 height)                                                                                      \
        : _Width((t2Cast)width)                                                                                       \
        , _Height((t2Cast)height)                                                                                     \
    {                                                                                                                 \
    }                                                                                                                 \
    DynSize(t1 width, t2 height)                                                                                      \
        : _Width((t1Cast)width)                                                                                       \
        , _Height((t2Cast)height)                                                                                     \
    {                                                                                                                 \
    }                                                                                                                 \
    DynSize(t2 width, t1 height)                                                                                      \
        : _Width((t2Cast)width)                                                                                       \
        , _Height((t1Cast)height)                                                                                     \
    {                                                                                                                 \
    }

#define INDEX_UI_DynSize_Constructor_FirstType_SecondType(t1, t2)                                                     \
    DynSize(t1 width, t2 height)                                                                                      \
        : _Width(width)                                                                                               \
        , _Height(height)                                                                                             \
    {                                                                                                                 \
    }                                                                                                                 \
    DynSize(t2 width, t1 height)                                                                                      \
        : _Width(width)                                                                                               \
        , _Height(height)                                                                                             \
    {                                                                                                                 \
    }

#define INDEX_UI_DynSize_Constructor_Cast_FirstType_SecondType(t1, t2, t1Cast, t2Cast)                                \
    DynSize(t1 width, t2 height)                                                                                      \
        : _Width((t1Cast)width)                                                                                       \
        , _Height((t2Cast)height)                                                                                     \
    {                                                                                                                 \
    }                                                                                                                 \
    DynSize(t2 width, t1 height)                                                                                      \
        : _Width((t2Cast)width)                                                                                       \
        , _Height((t1Cast)height)                                                                                     \
    {                                                                                                                 \
    }

    struct DynSize
    {
        using DynFloat = float;
        using DynFunc = Func<float()>;
        using DynThatFunc = Func<float(UIDynamic* that, UIContext* u)>;
        using DynSizeFunc = Func<Size()>;
        using DynSizeThatFunc = Func<Size(UIDynamic* that, UIContext* u)>;
        static constexpr size_t Index_DynFloat = 0;
        static constexpr size_t Index_DynFunc = 1;
        static constexpr size_t Index_DynThatFunc = 2;
        static constexpr size_t Index_Size_DynSizeFunc = 0;
        static constexpr size_t Index_Size_DynSizeThatFunc = 1;

    private:
        Nullable<Variant<DynSizeFunc, DynSizeThatFunc>> _Size;
        Nullable<Variant<DynFloat, DynFunc, DynThatFunc>> _Width;
        Nullable<Variant<DynFloat, DynFunc, DynThatFunc>> _Height;

    public:
        Size CachedSize;

    public:
        __forceinline float GetWidthCache(UIDynamic* that, UIContext* u)
        {
            if (!_Width.HasValue) return 0;
            auto& v = _Width.Value;
            switch (v.Index)
            {
            case Index_DynFloat:
            {
                return v.Get<DynFloat>();
                break;
            }
            case Index_DynFunc:
            {
                auto& val = v.Get<DynFunc>();
                return val();
                break;
            }
            case Index_DynThatFunc:
            {
                auto& val = v.Get<DynThatFunc>();
                return val(that, u);
                break;
            }
            default:
                return 0;
            }
        }

        __forceinline float GetHeightCache(UIDynamic* that, UIContext* u)
        {
            if (!_Height.HasValue) return 0;
            auto& v = _Height.Value;
            switch (v.Index)
            {
            case Index_DynFloat:
            {
                return v.Get<DynFloat>();
                break;
            }
            case Index_DynFunc:
            {
                auto& val = v.Get<DynFunc>();
                return val();
                break;
            }
            case Index_DynThatFunc:
            {
                auto& val = v.Get<DynThatFunc>();
                return val(that, u);
                break;
            }
            default:
                return 0;
            }
        }

        __forceinline Size GetSizeCache(UIDynamic* that, UIContext* u)
        {
            if (!_Size.HasValue) return {};
            auto& v = _Size.Value;
            switch (v.Index)
            {
            case Index_Size_DynSizeFunc:
            {
                auto& val = v.Get<DynSizeFunc>();
                return val();
                break;
            }
            case Index_Size_DynSizeThatFunc:
            {
                auto& val = v.Get<DynSizeThatFunc>();
                return val(that, u);
                break;
            }
            default:
                return {};
            }
        }

        __forceinline Size GetCache(UIDynamic* that, UIContext* u)
        {
            if (_Size.HasValue) { return GetSizeCache(that, u); }
            return { GetWidthCache(that, u), GetHeightCache(that, u) };
        }

        __forceinline void CacheContent(UIDynamic* that, UIContext* u) { CachedSize = GetCache(that, u); }

    public:
        INDEX_UI_DynSize_Constructor_All_Cast_FirstType_SecondType(float, int, float, float);
        INDEX_UI_DynSize_Constructor_FirstType_SecondType(float, DynFunc);
        INDEX_UI_DynSize_Constructor_FirstType_SecondType(float, DynThatFunc);
        INDEX_UI_DynSize_Constructor_Cast_FirstType_SecondType(int, DynFunc, float, DynFunc);
        INDEX_UI_DynSize_Constructor_Cast_FirstType_SecondType(int, DynThatFunc, float, DynThatFunc);
    };
}

// UI Stuff
namespace Index::UI
{
    // UIPath
    struct UIPath
    {
        template <class... TArgs> static UIPath From(TArgs&&... args)
        {
            auto ret = UIPath();
            ret.Path = { "?" };
            (ret.Path.Push(args), ...);
            if (ret.Path.Length == 0) throw "Invalid path.";
            return ret;
        }

        static UIPath Parse(String path)
        {
            auto ret = UIPath();
            ret.Path = { "?" };
            for (auto& c : path.Split(" "))
            {
                ret.Path.Push(c);
            }
            if (ret.Path.Length == 0) throw "Invalid path.";
            return ret;
        }

        List<string> Path;

        string GetCurrent() { return Path.First; }

        INDEX_Property(get = GetCurrent) string Current;

        void Next()
        {
            if (Path.Length <= 1) throw "Cannot go deeper.";
            Path.Erase(Path.begin());
        }

        string GetElementName() { return Path.Last; }

        INDEX_Property(get = GetElementName) string ElementName;

        bool GetIsNavigating() { return Path.Length != 1; }

        INDEX_Property(get = GetIsNavigating) bool IsNavigating;
    };

    namespace NotificationId
    {
        constexpr Int64 None = -1;
        constexpr Int64 Unknown = 0;
        constexpr Int64 FindElement = 0;
    }

    // UINotification
    struct UINotification
    {
        UINotification(Int64 id, UIContext* context)
            : Id(id)
            , Context(context)
        {
        }

        virtual ~UINotification() { }

        UIContext* Context;
        bool Handled = false;
        const Int64 Id = -1;
    };

    // FindElementN
    struct FindElementN : virtual UINotification
    {
        FindElementN(UIContext* context, UIPath path)
            : UINotification(NotificationId::FindElement, context)
        {
            Path = path;
            ElementName = path.ElementName;
        }

        UIPath Path;
        string ElementName;

        bool GetIsNavigating() { return Path.IsNavigating; }

        INDEX_Property(get = GetIsNavigating) bool IsNavigating;

        bool GetMoveOut() { return Path.Path.Length > 1 && Path.ElementName == "^"; }

        INDEX_Property(get = GetMoveOut) bool MoveOut;

        bool GetMoveIn() { return Path.Path.Length > 1 && Path.ElementName != "^"; }

        INDEX_Property(get = GetMoveIn) bool MoveIn;
        WPtr<UIElement> Result;

        void Close(WPtr<UIElement> e)
        {
            Result = e;
            Handled = true;
        }
    };

    // Layout
    struct Layout
    {
        Rect Area;

        bool operator==(const Layout& other) const = default;

        bool operator!=(const Layout& other) const = default;

        [[nodiscard]] float GetWidth() const { return Area.Width; }

        void SetWidth(float value) { Area.Width = value; }

        INDEX_Property(get = GetWidth, put = SetWidth) float Width;

        [[nodiscard]] float GetHeight() const { return Area.Height; }

        void SetHeight(float value) { Area.Height = value; }

        INDEX_Property(get = GetHeight, put = SetHeight) float Height;
    };

    // UIElementCache
    struct UIElementLayoutCache
    {
        Nullable<Layout> LastLayout;
        Nullable<Size> LastIntentSize;
        bool UseCachedSize = false;

        void CacheLayout(Layout i);
    };

    // UIElement
    struct UIElement : IObj<UIElement>
    {
        UIElementLayoutCache Cache {};
        string Name;
        Size MinSize { 0, 0 };
        Size MaxSize { NullF, NullF };
        Size Size { NullF, NullF };
        Align Alignment = Align::Stretch;

        virtual void Render(UIContext* u, Layout i) = 0;

        virtual void Notify(UINotification* e);

        virtual void OnNotify(UINotification* e) = 0;

        virtual Index::Size MeasureIntentSize(Layout i);
    };

    // UIElementHolder
    struct UIElementHolder : virtual UIElement
    {
        List<IPtr<UIElement>> Content;
    };

    // UIScope
    struct UIScope : virtual UIElement
    {
    private:
        UIScope* ParentScope;
        UIContext* CurrentContext;

    protected:
        void EnterScope(UIContext* u);

        void LeaveScope();

    public:
        void Notify(UINotification* e) override;
    };

    // UIDynamic
    struct UIDynamic : virtual UIElement
    {
        DynSize DynMinSize { 0.0f, 0.0f };
        DynSize DynMaxSize { NullF, NullF };
        DynSize DynSize { NullF, NullF };

        __forceinline void DynCache(UIContext* u)
        {
            DynMinSize.CacheContent(this, u);
            DynMaxSize.CacheContent(this, u);
            DynSize.CacheContent(this, u);
            UIElement::MinSize = DynMinSize.CachedSize;
            UIElement::MaxSize = DynMaxSize.CachedSize;
            UIElement::Size = DynSize.CachedSize;
        }
    };

    // UIContext
    struct UIContext
    {
        inline explicit UIContext();

        inline ~UIContext();

        using TimeSpan = typename std::chrono::duration<double>;

        IPtr<UIElement> Root;
        UIScope* Scope;

        TimeSpan _DeltaTime;

        TimeSpan GetDeltaTime();

        void SetDeltaTime(TimeSpan deltaTime);

        INDEX_Property(get = GetDeltaTime, put = SetDeltaTime) TimeSpan DeltaTime;
        double _Delta = 0;

        double GetDelta();

        INDEX_Property(get = GetDelta) double Delta;

        virtual void Notify(UINotification* e) = 0;

        template <class TType = UIElement, class... TArgs> __forceinline WPtr<TType> FindA(TArgs&&... args);

        template <class TType = UIElement, class... TArgs> __forceinline WPtr<TType> TryFindA(TArgs&&... args);

        template <class TType = UIElement> __forceinline WPtr<TType> Find(String path);

        template <class TType = UIElement> __forceinline WPtr<TType> TryFind(String path);

        virtual WPtr<UIElement> FindElement(UIPath path);

        virtual WPtr<UIElement> TryFindElement(UIPath path);

        inline void SetRoot(IPtr<UIElement> root);
    };
}

// ##################################### //
#pragma endregion
// ##################################### //

// ##################################### //
#pragma region Implementation
// ##################################### //

#pragma region Important

Index::Vec2F Index::Min(Vec2F v1, Vec2F v2) { return { Index::Min(v1.X, v2.X), Index::Min(v1.Y, v2.Y) }; }

Index::Vec2F Index::Max(Vec2F v1, Vec2F v2) { return { Index::Max(v1.X, v2.X), Index::Max(v1.Y, v2.Y) }; }

Index::Size Index::Min(Size v1, Size v2)
{
    return { Index::Min(v1.Width, v2.Width), Index::Min(v1.Height, v2.Height) };
}

Index::Size Index::Max(Size v1, Size v2)
{
    return { Index::Max(v1.Width, v2.Width), Index::Max(v1.Height, v2.Height) };
}

float Index::UI::Validate(float v1, float $else = 0) { return v1 != NullF ? v1 : $else; }

float Index::UI::Validate2(float v1, float v2, float $else = 0) { return Validate(v1, Validate(v2, $else)); }

float Index::UI::Validate3(float v1, float v2, float v3, float $else = 0)
{
    return Validate2(v1, v2, Validate(v3, $else));
    ;
}

Index::Vec2F Index::UI::Validate(Vec2F v1, Vec2F $else = { NullF, 0 })
{
    return { v1.X != NullF ? v1.X : $else.X, v1.Y != NullF ? v1.Y : $else.Y };
}

Index::Vec2F Index::UI::Validate2(Vec2F v1, Vec2F v2, Vec2F $else = { 0, 0 })
{
    return Validate(v1, Validate(v2, $else));
}

Index::Vec2F Index::UI::Validate3(Vec2F v1, Vec2F v2, Vec2F v3, Vec2F $else = { 0, 0 })
{
    return Validate2(v1, v2, Validate(v3, $else));
}

Index::Size Index::UI::Validate(Size v1, Size $else = { 0, 0 })
{
    return { v1.Width != NullF ? v1.Width : $else.Width, v1.Height != NullF ? v1.Height : $else.Height };
}

Index::Size Index::UI::Validate2(Size v1, Size v2, Size $else = { 0, 0 }) { return Validate(v1, Validate(v2, $else)); }

Index::Size Index::UI::Validate3(Size v1, Size v2, Size v3, Size $else = { 0, 0 })
{
    return Validate2(v1, v2, Validate(v3, $else));
}

Index::Size Index::UI::GetMinSize(UIElement* e)
{
    /*
     * Size Priority:
     * 1. MaxSize
     * 2. MinSize
     * 3. Size
     */
    auto size = e->Size;
    auto minSize = e->MinSize;
    auto maxSize = e->MaxSize;
    return { size.Width != NullF ? size.Width : Index::Min(Validate(minSize.Width), maxSize.Width),
        size.Height != NullF ? size.Height : Index::Min(Validate(minSize.Height), maxSize.Height) };
}

Index::Size Index::UI::GetMaxSize(UIElement* e)
{
    auto size = e->Size;
    auto maxSize = e->MaxSize;
    return { size.Width != NullF ? size.Width : maxSize.Width, size.Height != NullF ? size.Height : maxSize.Height };
}

Index::Rect Index::UI::AlignRect(Rect box, Size content, Align align)
{
    Rect r {};
#pragma region Horizontal
    if (align.IsHStretched)
    {
        r.Width = Index::Max(box.Width, content.Width);
        r.X = box.Center.X - (r.Width / 2);
    }
    if (align.IsHCentered)
    {
        r.Width = content.Width;
        r.X = box.Center.X - (r.Width / 2);
    }
    if (align.IsHLeft)
    {
        r.Width = content.Width;
        r.X = box.First.X;
    }
    if (align.IsHRight)
    {
        r.Width = content.Width;
        r.X = box.Second.X - r.Width;
    }
#pragma endregion
#pragma region Vertical
    if (align.IsVStretched)
    {
        r.Height = Index::Max(box.Height, content.Height);
        r.Y = box.Center.Y - (r.Height / 2);
    }
    if (align.IsVCentered)
    {
        r.Height = content.Height;
        r.Y = box.Center.Y - (r.Height / 2);
    }
    if (align.IsVTop)
    {
        r.Height = content.Height;
        r.Y = box.First.Y;
    }
    if (align.IsVBottom)
    {
        r.Height = content.Height;
        r.Y = box.Second.Y - r.Height;
    }
#pragma endregion
    return r;
}

Index::Rect Index::UI::AlignRectNoStretch(Rect box, Size content, Align align)
{
    Rect r {};
#pragma region Horizontal
    if (align.IsHStretched || align.IsHCentered)
    {
        r.Width = content.Width;
        r.X = box.Center.X - (r.Width / 2);
    }
    if (align.IsHLeft)
    {
        r.Width = content.Width;
        r.X = box.First.X;
    }
    if (align.IsHRight)
    {
        r.Width = content.Width;
        r.X = box.Second.X - r.Width;
    }
#pragma endregion
#pragma region Vertical
    if (align.IsVStretched || align.IsVCentered)
    {
        r.Height = content.Height;
        r.Y = box.Center.Y - (r.Height / 2);
    }
    if (align.IsVTop)
    {
        r.Height = content.Height;
        r.Y = box.First.Y;
    }
    if (align.IsVBottom)
    {
        r.Height = content.Height;
        r.Y = box.Second.Y - r.Height;
    }
#pragma endregion
    return r;
}

Index::Rect Index::UI::AlignRectWithMaxSize(Rect box, Size content, Size maxSize, Align align)
{
    Rect r {};
#pragma region Horizontal
    if (align.IsHStretched)
    {
        r.Width = Index::Max(box.Width, content.Width);
        r.Width = Index::Min(r.Width, maxSize.Width);
        r.X = box.Center.X - (r.Width / 2);
    }
    if (align.IsHCentered)
    {
        r.Width = content.Width;
        r.Width = Index::Min(r.Width, maxSize.Width);
        r.X = box.Center.X - (r.Width / 2);
    }
    if (align.IsHLeft)
    {
        r.Width = content.Width;
        r.Width = Index::Min(r.Width, maxSize.Width);
        r.X = box.First.X;
    }
    if (align.IsHRight)
    {
        r.Width = content.Width;
        r.Width = Index::Min(r.Width, maxSize.Width);
        r.X = box.Second.X - r.Width;
    }
#pragma endregion
#pragma region Vertical
    if (align.IsVStretched)
    {
        r.Height = Index::Max(box.Height, content.Height);
        r.Height = Index::Min(r.Height, maxSize.Height);
        r.Y = box.Center.Y - (r.Height / 2);
    }
    if (align.IsVCentered)
    {
        r.Height = content.Height;
        r.Height = Index::Min(r.Height, maxSize.Height);
        r.Y = box.Center.Y - (r.Height / 2);
    }
    if (align.IsVTop)
    {
        r.Height = content.Height;
        r.Height = Index::Min(r.Height, maxSize.Height);
        r.Y = box.First.Y;
    }
    if (align.IsVBottom)
    {
        r.Height = content.Height;
        r.Height = Index::Min(r.Height, maxSize.Height);
        r.Y = box.Second.Y - r.Height;
    }
#pragma endregion
    return r;
}

Index::Rect Index::UI::GetSubrect(UIElement* e, Layout i)
{
    Align align = e->Alignment;
    Rect box = i.Area;
    Size content = Max(GetMinSize(e), e->MeasureIntentSize(i));
    Size maxSize = GetMaxSize(e);
    Rect r {};
#pragma region Horizontal
    if (align.IsHStretched)
    {
        r.Width = Index::Max(box.Width, content.Width);
        r.Width = Index::Min(r.Width, maxSize.Width);
        r.X = box.Center.X - (r.Width / 2);
    }
    if (align.IsHCentered)
    {
        r.Width = content.Width;
        r.Width = Index::Min(r.Width, maxSize.Width);
        r.X = box.Center.X - (r.Width / 2);
    }
    if (align.IsHLeft)
    {
        r.Width = content.Width;
        r.Width = Index::Min(r.Width, maxSize.Width);
        r.X = box.First.X;
    }
    if (align.IsHRight)
    {
        r.Width = content.Width;
        r.Width = Index::Min(r.Width, maxSize.Width);
        r.X = box.Second.X - r.Width;
    }
#pragma endregion
#pragma region Vertical
    if (align.IsVStretched)
    {
        r.Height = Index::Max(box.Height, content.Height);
        r.Height = Index::Min(r.Height, maxSize.Height);
        r.Y = box.Center.Y - (r.Height / 2);
    }
    if (align.IsVCentered)
    {
        r.Height = content.Height;
        r.Height = Index::Min(r.Height, maxSize.Height);
        r.Y = box.Center.Y - (r.Height / 2);
    }
    if (align.IsVTop)
    {
        r.Height = content.Height;
        r.Height = Index::Min(r.Height, maxSize.Height);
        r.Y = box.First.Y;
    }
    if (align.IsVBottom)
    {
        r.Height = content.Height;
        r.Height = Index::Min(r.Height, maxSize.Height);
        r.Y = box.Second.Y - r.Height;
    }
#pragma endregion
    return r;
}

Index::Rect Index::UI::GetSubrectWithCustomIntentSize(UIElement* e, Layout i, Size intentSize)
{
    Align align = e->Alignment;
    Rect box = i.Area;
    Size content = Max(GetMinSize(e), intentSize);
    Size maxSize = GetMaxSize(e);
    Rect r {};
#pragma region Horizontal
    if (align.IsHStretched)
    {
        r.Width = Index::Max(box.Width, content.Width);
        r.Width = Index::Min(r.Width, maxSize.Width);
        r.X = box.Center.X - (r.Width / 2);
    }
    if (align.IsHCentered)
    {
        r.Width = content.Width;
        r.Width = Index::Min(r.Width, maxSize.Width);
        r.X = box.Center.X - (r.Width / 2);
    }
    if (align.IsHLeft)
    {
        r.Width = content.Width;
        r.Width = Index::Min(r.Width, maxSize.Width);
        r.X = box.First.X;
    }
    if (align.IsHRight)
    {
        r.Width = content.Width;
        r.Width = Index::Min(r.Width, maxSize.Width);
        r.X = box.Second.X - r.Width;
    }
#pragma endregion
#pragma region Vertical
    if (align.IsVStretched)
    {
        r.Height = Index::Max(box.Height, content.Height);
        r.Height = Index::Min(r.Height, maxSize.Height);
        r.Y = box.Center.Y - (r.Height / 2);
    }
    if (align.IsVCentered)
    {
        r.Height = content.Height;
        r.Height = Index::Min(r.Height, maxSize.Height);
        r.Y = box.Center.Y - (r.Height / 2);
    }
    if (align.IsVTop)
    {
        r.Height = content.Height;
        r.Height = Index::Min(r.Height, maxSize.Height);
        r.Y = box.First.Y;
    }
    if (align.IsVBottom)
    {
        r.Height = content.Height;
        r.Height = Index::Min(r.Height, maxSize.Height);
        r.Y = box.Second.Y - r.Height;
    }
#pragma endregion
    return r;
}

Index::Size Index::UI::GetIntentSizeFrom(Layout i, List<IPtr<UIElement>>& content)
{
    float minWidth = 0, minHeight = 0;
    for (auto& c : content)
    {
        if (c.IsNull) continue;
        auto size = c->MeasureIntentSize(std::forward<Layout>(i));
        minWidth = Index::Max(minWidth, size.Width);
        minHeight = Index::Max(minHeight, size.Height);
    }
    return { minWidth, minHeight };
}

#pragma endregion

#pragma region UIStuff

// UIElementLayoutCache
inline void Index::UI::UIElementLayoutCache::CacheLayout(Layout i) { }

// UIElement
inline void Index::UI::UIElement::Notify(UINotification* e)
{
    if (e->Id == NotificationId::FindElement && !Name.IsEmpty)
    {
        auto findElementN = dynamic_cast<FindElementN*>(e);
        if (!findElementN) throw "Invalid id.";
        if (!findElementN->IsNavigating)
        {
            if (Name == findElementN->ElementName || findElementN->ElementName == "?")
            {
                findElementN->Close(WSelf());
            }
        }
    }
    OnNotify(e);
}

inline Index::Size Index::UI::UIElement::MeasureIntentSize(Layout i)
{
    if (Cache.LastLayout.HasValue && Cache.LastIntentSize.HasValue)
    {
        if (Cache.LastLayout.Value == i) { return Cache.LastIntentSize.Value; }
    }
    auto ret = GetMinSize(this);
    Cache.LastLayout = i;
    Cache.LastIntentSize = ret;
    return ret;
}

// UIScope
inline void Index::UI::UIScope::EnterScope(UIContext* u)
{
    CurrentContext = u;
    ParentScope = u->Scope;
    u->Scope = this;
}

inline void Index::UI::UIScope::LeaveScope()
{
    CurrentContext->Scope = ParentScope;
    CurrentContext = nullptr;
    ParentScope = nullptr;
}

inline void Index::UI::UIScope::Notify(Index::UI::UINotification* e)
{
    if (e->Id == NotificationId::FindElement)
    {
        auto findElementN = dynamic_cast<FindElementN*>(e);
        if (!findElementN) throw "Invalid id.";
        if (findElementN->IsNavigating)
        {
            if (findElementN->MoveOut)
            {
                findElementN->Path.Next();
                ParentScope->Notify(e);
            }
            else if (findElementN->MoveIn)
            {
                if (Name == findElementN->Path.Current || findElementN->Path.Current == "?")
                {
                    findElementN->Path.Next();
                    if (e->Context->Scope != this)
                    {
                        EnterScope(e->Context);
                        OnNotify(e);
                        LeaveScope();
                    }
                    else
                    {
                        OnNotify(e);
                    }
                }
            }
        }
        else
        {
            if (Name == findElementN->ElementName) { findElementN->Close(WSelf()); }
            else
            {
                OnNotify(e);
            }
        }
    }
    else
        UIElement::Notify(e);
}

// UIContext
Index::UI::UIContext::UIContext()
{
    // Created();
}

Index::UI::UIContext::~UIContext()
{
    // Closing();
}

inline Index::UI::UIContext::TimeSpan Index::UI::UIContext::GetDeltaTime() { return _DeltaTime; }

inline void Index::UI::UIContext::SetDeltaTime(Index::UI::UIContext::TimeSpan deltaTime)
{
    _DeltaTime = deltaTime;
    _Delta = deltaTime.count();
}

inline double Index::UI::UIContext::GetDelta() { return _Delta; }

template <class TType, class... TArgs> inline Index::WPtr<TType> Index::UI::UIContext::FindA(TArgs&&... args)
{
    if constexpr (std::is_same_v<UIElement, TType>) { return FindElement(UIPath::From(std::forward<TArgs>(args)...)); }
    else
    {
        return FindElement(UIPath::From(std::forward<TArgs>(args)...)).template DynamicAs<TType>();
    }
}

template <class TType, class... TArgs> inline Index::WPtr<TType> Index::UI::UIContext::TryFindA(TArgs&&... args)
{
    if constexpr (std::is_same_v<UIElement, TType>)
    {
        return TryFindElement(UIPath::From(std::forward<TArgs>(args)...));
    }
    else
    {
        return TryFindElement(UIPath::From(std::forward<TArgs>(args)...)).template DynamicAs<TType>();
    }
}

template <class TType> inline Index::WPtr<TType> Index::UI::UIContext::Find(String s)
{
    if constexpr (std::is_same_v<UIElement, TType>) { return FindElement(UIPath::Parse(std::forward<String>(s))); }
    else
    {
        return FindElement(UIPath::Parse(std::forward<String>(s))).template DynamicAs<TType>();
    }
}

template <class TType> inline Index::WPtr<TType> Index::UI::UIContext::TryFind(String s)
{
    if constexpr (std::is_same_v<UIElement, TType>) { return FindElement(UIPath::Parse(std::forward<String>(s))); }
    else
    {
        return FindElement(UIPath::Parse(std::forward<String>(s))).template DynamicAs<TType>();
    }
}

inline Index::WPtr<Index::UI::UIElement> Index::UI::UIContext::FindElement(UIPath path)
{
    auto e = FindElementN(this, path);
    this->Scope->Notify(&e);
    if (e.Result.IsNull) throw "Result was Null.";
    return e.Result;
}

inline Index::WPtr<Index::UI::UIElement> Index::UI::UIContext::TryFindElement(UIPath path)
{
    auto e = FindElementN(this, path);
    this->Scope->Notify(&e);
    return e.Result;
}

inline void Index::UI::UIContext::SetRoot(IPtr<UIElement> root) { Root = std::move(root); }

#pragma endregion

// ##################################### //
#pragma endregion
// ##################################### //