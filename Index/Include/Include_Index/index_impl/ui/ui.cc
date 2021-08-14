#pragma once

#include <variant>

#include "../core/include.cc"
#include "../std/include.cc"

// Important
namespace Index::UI
{
    // NullF: The Float value that represents Null
    constexpr float NullF = Limits::FloatMax;

    // If value is not NullF then value else other
    constexpr float FloatValueOr(float value, float other) {
        return value == NullF ? other : value;
    }

    // If value is not NullF then value else other
    constexpr float FloatValueOr(float value1, float value2, float other) {
        return FloatValueOr(value2, FloatValueOr(value1, other));
    }

    // If value is not NullF then value else other
    constexpr float FloatValueOr(float value1, float value2, float value3, float other) {
        return FloatValueOr(value3, FloatValueOr(value2, FloatValueOr(value1, other)));
    }

    __forceinline Rect AlignRect(Rect box, Size content, Align align, Size minSize = {0, 0}) {
        Rect r;
        if (align.IsHStretched) {
            r.X = box.X;
            r.Width = r.Width;
        }
        if (align.IsHLeft) {
            r.X = box.X;
            r.Width = minSize.Width;
        }
        if (align.IsHCentered) {
            r.X = box.X + ((box.Width - Max(0.f, minSize.Width)) / 2);
            r.Width = minSize.Width;
        }
        if (align.IsHRight) {
            r.X = box.X + (box.Width - Max(0.f, minSize.Width));
            r.Width = minSize.Width;
        }
        if (align.IsVStretched) {
            r.Y = box.Y;
            r.Height = minSize.Height;
        }
        if (align.IsVTop) {
            r.X = box.X;
            r.Height = minSize.Height;
        }
        if (align.IsVCentered) {
            r.Y = box.X + ((box.Height - Max(0.f, minSize.Height)) / 2);
            r.Height = minSize.Height;
        }
        if (align.IsVBottom) {
            r.Y = box.X + (box.Height - Max(0.f, minSize.Height));
            r.Height = minSize.Height;
        }
        return r;
    }
}

// Structs
namespace Index::UI
{
    struct IRenderState;
    struct UIElement;
    struct LayoutInfo;
    struct State;
}

/// Values
namespace Index::UI::UIContext
{
    extern bool RebuildTree;
    extern IPtr<State> Root;
    extern Stack<IRenderState*> CurrentStates;
}

// Notification
namespace Index::UI
{
    struct INotification
    {
        bool Handled = false;
        Int64 Id = -1;
    };
}

// Layout
namespace Index::UI
{
    struct Layout
    {
        Rect Area;
        [[nodiscard]] float GetWidth() const { return Area.Width; }
        void SetWidth(float value) { Area.Width = value; }
        __declspec(property(get = GetWidth, put = SetWidth)) float Width;
        [[nodiscard]] float GetHeight() const { return Area.Height; }
        void SetHeight(float value) { Area.Height = value; }
        __declspec(property(get = GetHeight, put = SetHeight)) float Height;
    };
};

// RenderCommands
namespace Index::UI
{
    typedef Func<void()> IRenderCommand;

    struct IRenderState
    {
        List<std::variant<IRenderCommand, IRenderState*>> RenderList;
        void Render() {
            for (auto r : RenderList) {
                if (std::holds_alternative<IRenderCommand>(r)) {
                    auto func = std::get<IRenderCommand>(r);
                    if (func) func();
                }
                else {
                    auto renderState = std::get<IRenderState*>(r);
                    if (renderState) renderState->Render();
                }
            }
        }
        void ClearRenderList() {
            RenderList.Clear();
        }
        void AddCommand(IRenderCommand command) {
            RenderList.Push(command);
        }
        void AddState(IRenderState* state) {
            if (!state) return;
            RenderList.Push(state);
        }
    };
}

// UILayout
namespace Index::UI
{
    struct UILayout
    {

    };
};

// UIElement
namespace Index::UI
{
    struct UIElement
    {
        Size MinSize { NullF, NullF };
        Size MaxSize { NullF, NullF };
        Size Size { NullF, NullF };
        Align Alignment = Align::Stretch;
        virtual void Build(Layout i) = 0;
        virtual void Notify(INotification* e) = 0;
        virtual Index::Size MeasureMinSize();
    };
}

// LayoutUtils
namespace Index::UI::LayoutUtils
{
    inline Size CalculateMinSize(UIElement* element) {
        float minWidth = Min(Min(element->Size.Width, element->MaxSize.Width), FloatValueOr(element->MinSize.Width, 0));
        float minHeight = Min(Min(element->Size.Height, element->MaxSize.Height), FloatValueOr(element->MinSize.Height, 0));
        return { minWidth, minHeight };
    }
    inline Size CalculateMinSize(Size size, Size minSize, Size maxSize = { NullF, NullF }) {
        float minWidth = Min(Min(size.Width, maxSize.Width), FloatValueOr(size.Width, 0));
        float minHeight = Min(Min(size.Height, maxSize.Height), FloatValueOr(size.Height, 0));
        return { minWidth, minHeight };
    }
    inline float CalculateMinWidth(UIElement* element) {
        return Min(Min(element->Size.Width, element->MaxSize.Width), FloatValueOr(element->MinSize.Width, 0));
    }
    inline float CalculateMinHeight(UIElement* element) {
        return Min(Min(element->Size.Height, element->MaxSize.Height), FloatValueOr(element->MinSize.Height, 0));
    }
    inline float CalculateMinWidth(float width, float minWidth, float maxWidth = NullF) {
        return Min(Min(width, maxWidth), FloatValueOr(minWidth, 0));
    }
    inline float CalculateMinHeight(float height, float minHeight, float maxHeight = NullF) {
        return Min(Min(height, maxHeight), FloatValueOr(maxHeight, 0));
    }
    inline float CalculateMinWidth(Size size, Size minSize, Size maxSize = { NullF, NullF }) {
        return Min(Min(size.Width, maxSize.Width), FloatValueOr(size.Width, 0));
    }
    inline float CalculateMinHeight(Size size, Size minSize, Size maxSize = { NullF, NullF }) {
        return Min(Min(size.Height, maxSize.Height), FloatValueOr(size.Height, 0));
    }
    inline bool CanRectFitInto(Rect rect, Rect parent) {
        return rect.Width <= parent.Width && rect.Height <= parent.Height;
    }
    inline bool CanSizeFitInto(Size rect, Size parent) {
        return rect.Width <= parent.Width && rect.Height <= parent.Height;
    }
    inline Size CalculateMinSizeFrom(List<IPtr<UIElement>>& content) {
        float minWidth = 0;
        float minHeight = 0;
        for (auto& c : content) {
            auto size = c->MeasureMinSize();
            minWidth = Max(minWidth, size.Width);
            minHeight = Max(minHeight, size.Height);
        }
        return {
            minWidth, minHeight
        };
    }
    inline Rect CenterRect(Rect rect, Rect parent) {
        auto parentCenter = parent.Center;
        auto rectSize = rect.Size;
        return Rect {
            parentCenter.X - (rectSize.Width / 2),
            parentCenter.Y - (rectSize.Height / 2),
            rectSize
        };
    }
    inline Rect ClampCenterRect(Rect rect, Rect parent) {
        auto parentCenter = parent.Center;
        auto parentSize = parent.Size;
        auto rectSize = Size {
            Min(rect.Width, parent.Width),
            Min(rect.Height, parent.Height)
        };
        return Rect {
            parentCenter.X - (rectSize.Width / 2),
            parentCenter.Y - (rectSize.Height / 2),
            rectSize
        };
    }
    inline Rect AlignRect(Size minSize, Rect parent, Align a) {
        Size mins = {
            FloatValueOr(minSize.Width, 0),
            FloatValueOr(minSize.Height, 0)
        };
        Vec2F pos;
        Size size;
        if (a.IsHStretched) {
            size.Width = Max(mins.Width, parent.Width);
            pos.X = parent.Center.X - (size.Width / 2);
        }
        if (a.IsHCentered) {
            size.Width = mins.Width;
            pos.X = parent.Center.X - (size.Width / 2);
        }
        if (a.IsHLeft) {
            size.Width = mins.Width;
            pos.X = parent.First.X;
        }
        if (a.IsHRight) {
            size.Width = mins.Width;
            pos.X = parent.Second.X - size.Width;
        }
        if (a.IsVStretched) {
            size.Height = Max(mins.Height, parent.Height);
            pos.Y = parent.Center.Y - (size.Height / 2);
        }
        if (a.IsVCentered) {
            size.Height = mins.Height;
            pos.Y = parent.Center.Y - (size.Height / 2);
        }
        if (a.IsVTop) {
            size.Height = mins.Height;
            pos.Y = parent.First.Y;
        }
        if (a.IsVBottom) {
            size.Height = mins.Height;
            pos.Y = parent.Second.Y - size.Height;
        }
        return { pos, size };
    }
    inline Rect CalculateUIElementSubrect(UIElement* e, Layout i) {
        Align a = e->Alignment;
        Size mins = e->MeasureMinSize();
        Size maxs = e->MaxSize;
        Rect r = i.Area;
        return AlignRect(mins, r, e->Alignment);
    }
}

// UIElement Implementation
namespace Index::UI
{
    inline Index::Size UIElement::MeasureMinSize() {
        return LayoutUtils::CalculateMinSize(this);
    }
}

// State
namespace Index::UI
{
    struct State : UIElement, IRenderState
    {
        List<IPtr<UIElement>> Content;
        State() = default;
        explicit State(List<IPtr<UIElement>> content) {
            Content = std::move(content);
        }
        void Build(Layout i) override {
            (+UIContext::CurrentStates)->AddState(static_cast<IRenderState*>(this));
            if (!UIContext::RebuildTree) return;
            this->ClearRenderList();
            for (auto& c : Content) {
                if (c) c->Build(i);
            }
        }
        void Rebuild(Layout i) {
            bool isRebuilding = Index::UI::UIContext::RebuildTree;
            Index::UI::UIContext::RebuildTree = true;
            Build(i);
            Index::UI::UIContext::RebuildTree = isRebuilding;
        }
        void Notify(INotification* e) override {
            for (auto& c : Content) {
                Notify(e);
                if (e->Handled) return;
            }
        }
    };
}

/// Values
namespace Index::UI::UIContext
{
    inline bool RebuildTree = true;
    inline IPtr<State> Root;
    inline Stack<IRenderState*> CurrentStates;
}

/// Begin and End
namespace Index::UI::UIContext
{
    namespace {
        inline bool IsBuilding = false;
    }
    inline void BeginBuild() {
        if (IsBuilding) throw "The UI is already building.";
        RebuildTree = false;
        CurrentStates = Stack<IRenderState*>();
        IsBuilding = true;
    }
    inline void EndBuild() {
        if (!IsBuilding) throw "The UI isn't building.";
        RebuildTree = false;
        CurrentStates = Stack<IRenderState*>();
        IsBuilding = false;
    }
}

/// Render
namespace Index::UI::UIContext
{
    inline void Render() {
        if (IsBuilding) throw "Can't render while building.";
        if (Root.IsNull) throw "Root was Null";
        Root->Render();
    }
}