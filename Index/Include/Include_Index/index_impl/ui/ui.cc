#pragma once

#include <utility>
#include <variant>

#include "../core/include.cc"
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
    __forceinline Rect GetSubrect(UIElement* e, Layout i);
    __forceinline Size GetIntentSizeFrom(Layout i, List<IPtr<UIElement>>& content);
}

// Dynamic
namespace Index::UI
{
    // DynamicSizeCache
    struct DynamicSizeCache : Size
    {
        using Size::Size;
    };

    // DynamicSize
    struct DynamicSize
    {
        using DynamicFunc = Func<float()>;
        DynamicSizeCache Cache { };
        Variant<float, DynamicFunc> Width, Height;
        DynamicSize() = default;
        DynamicSize(float width, float height) : Width(width), Height(height) { }
        DynamicSize(Vec2F vec) : Width(vec.X), Height(vec.Y) { }
        void CacheContent() {
            if (Width.Has<float>()) {
                Cache.Width = Width.Get<float>();
            }
            else if (Width.Has<DynamicFunc>()) {
                auto& func = Width.Get<DynamicFunc>();
                if (func) Cache.Width = func();
            }
        }
    };
}

// UI Stuff
namespace Index::UI
{
    // UINotification
    struct UINotification
    {
        UIContext* Context;
        bool Handled = false;
        Int64 Id = -1;
    };

    // Layout
    struct Layout
    {
        Rect Area;
        bool operator==(const Layout& other) const = default;
        bool operator!=(const Layout& other) const = default;
        [[nodiscard]] float GetWidth() const { return Area.Width; }
        void SetWidth(float value) { Area.Width = value; }
        __declspec(property(get = GetWidth, put = SetWidth)) float Width;
        [[nodiscard]] float GetHeight() const { return Area.Height; }
        void SetHeight(float value) { Area.Height = value; }
        __declspec(property(get = GetHeight, put = SetHeight)) float Height;
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
    struct UIElement
    {
        UIElementLayoutCache Cache { };
        string Name;
        Size MinSize { 0, 0 };
        Size MaxSize { NullF, NullF };
        Size Size { NullF, NullF };
        Align Alignment = Align::Stretch;
        virtual void Render(UIContext* u, Layout i) = 0;
        virtual void Notify(UINotification* e) = 0;
        virtual Index::Size MeasureIntentSize(Layout i);
    };

    // UIElementHolder
    struct UIElementHolder : virtual UIElement
    {
        List<IPtr<UIElement>> Content;
    };

    // UIAnimation
    struct UIAnimation
    {

    };

    // UIDynamic
    struct UIDynamic : virtual UIElement
    {
        struct Size MinSize { 0, 0 };
        struct Size MaxSize { NullF, NullF };
        struct Size Size { NullF, NullF };
    };

    // UIContext
    struct UIContext
    {
        inline explicit UIContext();
        inline ~UIContext();

        using TimeSpan = typename std::chrono::duration<double>;

        IPtr<UIElement> Root;
        TimeSpan _DeltaTime;
        TimeSpan GetDeltaTime();
        void SetDeltaTime(TimeSpan deltaTime);
        __declspec(property(get = GetDeltaTime, put = SetDeltaTime)) TimeSpan DeltaTime;
        double _Delta = 0;
        double GetDelta();
        __declspec(property(get = GetDelta)) double Delta;

        virtual void Notify(UINotification* e) = 0;

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

Index::Vec2F Index::Min(Vec2F v1, Vec2F v2) {
    return {
        Index::Min(v1.X, v2.X),
        Index::Min(v1.Y, v2.Y)
    };
}

Index::Vec2F Index::Max(Vec2F v1, Vec2F v2) {
    return {
        Index::Max(v1.X, v2.X),
        Index::Max(v1.Y, v2.Y)
    };
}

Index::Size Index::Min(Size v1, Size v2) {
    return {
        Index::Min(v1.Width, v2.Width),
        Index::Min(v1.Height, v2.Height)
    };
}

Index::Size Index::Max(Size v1, Size v2) {
    return {
        Index::Max(v1.Width, v2.Width),
        Index::Max(v1.Height, v2.Height)
    };
}

float Index::UI::Validate(float v1, float $else = 0) {
    return v1 != NullF ? v1 : $else;
}

float Index::UI::Validate2(float v1, float v2, float $else = 0) {
    return Validate(v1, Validate(v2, $else));
}

float Index::UI::Validate3(float v1, float v2, float v3, float $else = 0) {
    return Validate2(v1, v2, Validate(v3, $else));;
}

Index::Vec2F Index::UI::Validate(Vec2F v1, Vec2F $else = { NullF, 0 }) {
    return {
        v1.X != NullF ? v1.X : $else.X,
        v1.Y != NullF ? v1.Y : $else.Y
    };
}

Index::Vec2F Index::UI::Validate2(Vec2F v1, Vec2F v2, Vec2F $else = { 0, 0 }) {
    return Validate(v1, Validate(v2, $else));
}

Index::Vec2F Index::UI::Validate3(Vec2F v1, Vec2F v2, Vec2F v3, Vec2F $else = { 0, 0 }) {
    return Validate2(v1, v2, Validate(v3, $else));
}

Index::Size Index::UI::Validate(Size v1, Size $else = { 0, 0 }) {
    return {
        v1.Width != NullF ? v1.Width : $else.Width,
        v1.Height != NullF ? v1.Height : $else.Height
    };
}

Index::Size Index::UI::Validate2(Size v1, Size v2, Size $else = { 0, 0 }) {
    return Validate(v1, Validate(v2, $else));
}

Index::Size Index::UI::Validate3(Size v1, Size v2, Size v3, Size $else = { 0, 0 }) {
    return Validate2(v1, v2, Validate(v3, $else));
}

Index::Size Index::UI::GetMinSize(UIElement *e) {
    /*
     * Size Priority:
     * 1. MaxSize
     * 2. MinSize
     * 3. Size
     */
    auto size = e->Size;
    auto minSize = e->MinSize;
    auto maxSize = e->MaxSize;
    return {
        size.Width != NullF ? size.Width : Min(Validate(minSize), Validate(maxSize)).Width,
        size.Height != NullF ? size.Height : Min(Validate(minSize), Validate(maxSize)).Height
    };
}

Index::Size Index::UI::GetMaxSize(UIElement *e) {
    return e->MaxSize;
}

Index::Rect Index::UI::AlignRect(Rect box, Size content, Align align) {
    Rect r { };
    #pragma region Horizontal
    if (align.IsHStretched) {
        r.Width = Index::Max(box.Width, content.Width);
        r.X = box.Center.X - (r.Width / 2);
    }
    if (align.IsHCentered) {
        r.Width = content.Width;
        r.X = box.Center.X - (r.Width / 2);
    }
    if (align.IsHLeft) {
        r.Width = content.Width;
        r.X = box.First.X;
    }
    if (align.IsHRight) {
        r.Width = content.Width;
        r.X = box.Second.X - r.Width;
    }
    #pragma endregion
    #pragma region Vertical
    if (align.IsVStretched) {
        r.Height = Index::Max(box.Height, content.Height);
        r.Y = box.Center.Y - (r.Height / 2);
    }
    if (align.IsVCentered) {
        r.Height = content.Height;
        r.Y = box.Center.Y - (r.Height / 2);
    }
    if (align.IsVTop) {
        r.Height = content.Height;
        r.Y = box.First.Y;
    }
    if (align.IsVBottom) {
        r.Height = content.Height;
        r.Y = box.Second.Y - r.Height;
    }
    #pragma endregion
    return r;
}

Index::Rect Index::UI::AlignRectNoStretch(Rect box, Size content, Align align)
{
    Rect r { };
    #pragma region Horizontal
    if (align.IsHStretched || align.IsHCentered) {
        r.Width = content.Width;
        r.X = box.Center.X - (r.Width / 2);
    }
    if (align.IsHLeft) {
        r.Width = content.Width;
        r.X = box.First.X;
    }
    if (align.IsHRight) {
        r.Width = content.Width;
        r.X = box.Second.X - r.Width;
    }
    #pragma endregion
    #pragma region Vertical
    if (align.IsVStretched || align.IsVCentered) {
        r.Height = content.Height;
        r.Y = box.Center.Y - (r.Height / 2);
    }
    if (align.IsVTop) {
        r.Height = content.Height;
        r.Y = box.First.Y;
    }
    if (align.IsVBottom) {
        r.Height = content.Height;
        r.Y = box.Second.Y - r.Height;
    }
    #pragma endregion
    return r;
}

Index::Rect Index::UI::GetSubrect(UIElement* e, Layout i) {
    Size size = e->MeasureIntentSize(i);
    Rect r = AlignRect(i.Area, size, e->Alignment);
    Size nsize = Min(GetMaxSize(e), r.Size);
    return AlignRectNoStretch(i.Area, nsize, e->Alignment);
}

Index::Size Index::UI::GetIntentSizeFrom(Layout i, List<IPtr<UIElement>>& content) {
    float minWidth = 0, minHeight = 0;
    for (auto& c : content) {
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
inline void Index::UI::UIElementLayoutCache::CacheLayout(Layout i) {

}

// UIElement
inline Index::Size Index::UI::UIElement::MeasureIntentSize(Layout i) {
    if (Cache.LastLayout.HasValue && Cache.LastIntentSize.HasValue) {
        if (Cache.LastLayout.Value == i) {
            return Cache.LastIntentSize.Value;
        }
    }
    auto ret = GetMinSize(this);
    Cache.LastLayout = i;
    Cache.LastIntentSize = ret;
    return ret;
}

// UIContext
Index::UI::UIContext::UIContext() {
    //Created();
}

Index::UI::UIContext::~UIContext() {
    //Closing();
}

inline Index::UI::UIContext::TimeSpan Index::UI::UIContext::GetDeltaTime()
{
    return _DeltaTime;
}

inline void Index::UI::UIContext::SetDeltaTime(Index::UI::UIContext::TimeSpan deltaTime)
{
    _DeltaTime = deltaTime;
    _Delta = deltaTime.count();
}

inline double Index::UI::UIContext::GetDelta()
{
    return _Delta;
}

inline void Index::UI::UIContext::SetRoot(IPtr<UIElement> root)
{
    Root = std::move(root);
}

#pragma endregion




// ##################################### //
#pragma endregion
// ##################################### //