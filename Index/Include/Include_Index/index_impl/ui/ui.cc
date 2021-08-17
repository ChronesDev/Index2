#pragma once

#include <utility>
#include <variant>

#include "../core/include.cc"
#include "../std/include.cc"




// ##################################### //
#pragma region Declaration
// ##################################### //



    // ##################################### //
    #pragma region Prototypes
    // ##################################### //




namespace Index::UI
{
    struct UINotification;
    struct Layout;
    struct UIElementCache;
    struct UIElement;
    struct UIElementHolder;
    struct UIContext;
}




    // ##################################### //
    #pragma endregion
    // ##################################### //




    // ##################################### //
    #pragma region Important
    // ##################################### //




namespace Index::UI
{
    // NullF: The Float value that represents Null
    constexpr float NullF = Limits::FloatMax;

    __forceinline Vec2F Min(Vec2F v1, Vec2F v2);
    __forceinline Vec2F Max(Vec2F v1, Vec2F v2);
    __forceinline Size Min(Size v1, Size v2);
    __forceinline Size Max(Size v1, Size v2);

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
    __forceinline Rect GetSubrect(UIElement* e, Layout i);
    __forceinline Size GetIntentSizeFrom(Layout i, List<IPtr<UIElement>>& content);
}




    // ##################################### //
    #pragma endregion
    // ##################################### //



    // ##################################### //
    #pragma region UIStuff
    // ##################################### //




namespace Index::UI
{




        // ##################################### //
        #pragma region INotification
        // ##################################### //

    struct UINotification
    {
        UIContext* Context;
        bool Handled = false;
        Int64 Id = -1;
    };

        // ##################################### //
        #pragma endregion
        // ##################################### //



        // ##################################### //
        #pragma region Layout
        // ##################################### //

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

        // ##################################### //
        #pragma endregion
        // ##################################### //



        // ##################################### //
        #pragma region UIElementCache
        // ##################################### //

    struct UIElementCache
    {
        Nullable<Layout> LastLayout;
        Nullable<Size> LastIntentSize;
    };

        // ##################################### //
        #pragma endregion
        // ##################################### //



        // ##################################### //
        #pragma region UIElement
        // ##################################### //

    struct UIElement
    {
        UIElementCache Cache { };
        Size MinSize { 0, 0 };
        Size MaxSize { NullF, NullF };
        Size Size { NullF, NullF };
        Align Alignment = Align::Stretch;
        virtual void Render(UIContext* u, Layout i) = 0;
        virtual void Notify(UINotification* e) = 0;
        virtual Index::Size MeasureIntentSize(Layout i);
    };

        // ##################################### //
        #pragma endregion
        // ##################################### //



        // ##################################### //
        #pragma region UIElementHolder
        // ##################################### //

    struct UIElementHolder : UIElement
    {
        List<IPtr<UIElement>> Content;
    };

        // ##################################### //
        #pragma endregion
        // ##################################### //



        // ##################################### //
        #pragma region UIContext
        // ##################################### //

    struct UIContext
    {
        explicit UIContext();
        ~UIContext();

        virtual void Created() = 0;
        virtual void Closing() = 0;

        IPtr<UIElement> Root;

        virtual void Render(Layout i) = 0;
        virtual void Notify(UINotification* e) = 0;

        void SetRoot(IPtr<UIElement> root);
    };

        // ##################################### //
        #pragma endregion
        // ##################################### //




}




    // ##################################### //
    #pragma endregion
    // ##################################### //




// ##################################### //
#pragma endregion
// ##################################### //



// ##################################### //
#pragma region Implementation
// ##################################### //




    #pragma region Important
Index::Vec2F Index::UI::Min(Vec2F v1, Vec2F v2) {
    return {
        Index::Min(v1.X, v2.X),
        Index::Min(v1.Y, v2.Y)
    };
}

Index::Vec2F Index::UI::Max(Vec2F v1, Vec2F v2) {
    return {
        Index::Max(v1.X, v2.X),
        Index::Max(v1.Y, v2.Y)
    };
}

Index::Size Index::UI::Min(Size v1, Size v2) {
    return {
        Index::Min(v1.Width, v2.Width),
        Index::Min(v1.Height, v2.Height)
    };
}

Index::Size Index::UI::Max(Size v1, Size v2) {
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
    auto vsize = Validate(e->Size);
    auto vminsize = Validate(e->MinSize);
    auto vsize2 = Max(vsize, vminsize);
    return Min(vsize2, e->MaxSize);
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

Index::Rect Index::UI::GetSubrect(UIElement* e, Layout i) {
    Size size = GetMinSize(e);
    return AlignRect(i.Area, size, e->Alignment);
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

        #pragma region UIElement
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
        #pragma endregion

        #pragma region UIContext
Index::UI::UIContext::UIContext() {
    Created();
}

Index::UI::UIContext::~UIContext() {
    Closing();
}

void Index::UI::UIContext::SetRoot(IPtr<UIElement> root) {
    Root = std::move(root);
}
        #pragma endregion

    #pragma endregion




// ##################################### //
#pragma endregion
// ##################################### //