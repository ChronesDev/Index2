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

// UIElement, State
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
        virtual LayoutInfo MeasureCenterSize();
        __forceinline Rect AlignContentRect(Layout i, Index::Size content, Index::Size minSize = {NullF, NullF}) {
            if (minSize.Width == NullF) {
                minSize.Width = 0;
            }
            if (minSize.Height == NullF) {
                minSize.Height = 0;
            }
            Rect r;
            if (Alignment.IsHStretched) {
                r.X = i.Area.X;
                r.Width = r.Width;
            }
            if (Alignment.IsHLeft) {
                r.X = i.Area.X;
                r.Width = minSize.Width;
            }
            if (Alignment.IsHCentered) {
                r.X = i.Area.X + ((i.Area.Width - Max(0.f, minSize.Width)) / 2);
                r.Width = minSize.Width;
            }
            if (Alignment.IsHRight) {
                r.X = i.Area.X + (i.Area.Width - Max(0.f, minSize.Width));
                r.Width = minSize.Width;
            }
            if (Alignment.IsVStretched) {
                r.Y = i.Area.Y;
                r.Height = minSize.Height;
            }
            if (Alignment.IsVTop) {
                r.X = i.Area.X;
                r.Height = minSize.Height;
            }
            if (Alignment.IsVCentered) {
                r.Y = i.Area.X + ((i.Area.Height - Max(0.f, minSize.Height)) / 2);
                r.Height = minSize.Height;
            }
            if (Alignment.IsVBottom) {
                r.Y = i.Area.X + (i.Area.Height - Max(0.f, minSize.Height));
                r.Height = minSize.Height;
            }
            return r;
        }
    };
}

// LayoutInfo
namespace Index::UI
{
    struct LayoutInfo
    {
        Size Size { NullF, NullF };
        [[nodiscard]] float GetWidth() const { return Size.Width; }
        void SetWidth(float value) { Size.Width = value; }
        __declspec(property(get = GetWidth, put = SetWidth)) float Width;
        [[nodiscard]] float GetHeight() const { return Size.Height; }
        void SetHeight(float value) { Size.Height = value; }
        __declspec(property(get = GetHeight, put = SetHeight)) float Height;
    public:
        static LayoutInfo FromList(List<IPtr<UIElement>>& content) {
            LayoutInfo i;
            float& w = i.Size.Width, h = i.Size.Height;
            for (auto& c : content) {
                if (!c) continue;
                auto info = c->MeasureCenterSize();
                if (info.Width != NullF) {
                    if (info.Width >= (w == NullF ? 0 : w)) {
                        w = info.Width;
                    }
                }
                if (info.Height != NullF) {
                    if (info.Height >= (h == NullF ? 0 : h)) {
                        h = info.Height;
                    }
                }
            }
            return i;
        }
        static LayoutInfo FromSpan(Span<UIElement*> content) {
            LayoutInfo i;
            float& w = i.Size.Width, h = i.Size.Height;
            for (auto& c : content) {
                if (!c) continue;
                auto info = c->MeasureCenterSize();
                if (info.Width != NullF) {
                    if (info.Width >= (w == NullF ? 0 : w)) {
                        w = info.Width;
                    }
                }
                if (info.Height != NullF) {
                    if (info.Height >= (h == NullF ? 0 : h)) {
                        h = info.Height;
                    }
                }
            }
            return i;
        }
        static LayoutInfo FromListAnd(List<IPtr<UIElement>>& content, UIElement* me) {
            LayoutInfo i;
            float& w = i.Size.Width, h = i.Size.Height;
            for (auto& c : content) {
                if (!c) continue;
                auto info = c->MeasureCenterSize();
                if (info.Width != NullF) {
                    if (info.Width >= (w == NullF ? 0 : w)) {
                        w = info.Width;
                    }
                }
                if (info.Height != NullF) {
                    if (info.Height >= (h == NullF ? 0 : h)) {
                        h = info.Height;
                    }
                }
            }

            {
                auto *c = me;
                if (!c) goto jmp_Continue;
                auto info = c->MeasureCenterSize();
                if (info.Width != NullF)
                {
                    if (info.Width >= (w == NullF ? 0 : w))
                    {
                        w = info.Width;
                    }
                }
                if (info.Height != NullF)
                {
                    if (info.Height >= (h == NullF ? 0 : h))
                    {
                        h = info.Height;
                    }
                }
            }
            jmp_Continue:

            return i;
        }
    };
}

// UIElement Implementation
namespace Index::UI
{
    inline LayoutInfo UIElement::MeasureCenterSize() {
        LayoutInfo i {
            .Size = {
                FloatValueOr(0, Size.Width, MinSize.Width),
                FloatValueOr(0, Size.Height, MinSize.Height)
            }
        };
        return i;
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

#define INDEX_UI_DEFAULT_NEW_MEBERS                             \
Index::Size MinSize { Index::UI::NullF, Index::UI::NullF };     \
Index::Size MaxSize { Index::UI::NullF, Index::UI::NullF };     \
Index::Size Size { Index::UI::NullF, Index::UI::NullF };        \
Index::Align Alignment = Index::Align::Stretch;

#define INDEX_UI_SET_DEFAULT_MEMBERS     \
this->MinSize = e.MinSize;               \
this->MaxSize = e.MaxSize;               \
this->Size = e.Size;                     \
this->Alignment = e.Alignment;


#define INDEX_UI_NEW_CLASS(class_name, properties) struct New {                                     \
    properties                                                                                      \
    operator Index::IPtr<Index::UI::UIElement>() {                                                  \
        return std::static_pointer_cast<Index::UI::UIElement>(Index::INew<class_name>(*this));      \
    }                                                                                               \
    operator Index::IPtr<class_name>() {                                                            \
        return Index::INew<class_name>(*this);                                                      \
    }                                                                                               \
    IPtr<Index::UI::UIElement> GetUIRef() {                                                         \
        return Index::INew<class_name>(*this);                                                      \
    }                                                                                               \
    __declspec(property(get = GetUIRef)) IPtr<Index::UI::UIElement> UIRef;                          \
};

#define INDEX_UI_NEW_CONSTRUCTOR(class_name) explicit class_name(New e)

#define INDEX_UI_THISSTATE (+Index::UI::UIContext::CurrentStates)

// Normal Elements
namespace Index::UI
{
    struct Empty : UIElement
    {
        INDEX_UI_NEW_CLASS(Empty,);
        INDEX_UI_NEW_CONSTRUCTOR(Empty) { }
        void Build(Layout i) override { }
        void Notify(INotification* e) override { }
    };

    struct Holder : UIElement
    {
        List<IPtr<UIElement>> Content;
        INDEX_UI_NEW_CLASS(Holder, List<IPtr<UIElement>> Content;);
        INDEX_UI_NEW_CONSTRUCTOR(Holder) {
            Content = std::move(e.Content);
        }
        void Build(Layout i) override {
            for (auto& c : Content) {
                if (c) c->Build(i);
            }
        }
        void Notify(INotification* e) override {
            for (auto& c : Content) {
                Notify(e);
                if (e->Handled) return;
            }
        }
        LayoutInfo MeasureCenterSize() override {
            return LayoutInfo::FromList(Content);
        }
    };

    struct Wrap : UIElement
    {
        IPtr<UIElement> Content;
        INDEX_UI_NEW_CLASS(Wrap, IPtr<UIElement> Content;);
        INDEX_UI_NEW_CONSTRUCTOR(Wrap) {
            Content = std::move(e.Content);
        }
        void Build(Layout i) override {
            if (Content) Content->Build(i);
        }
        void Notify(INotification* e) override {
            if (Content) Content->Notify(e);
        }
        LayoutInfo MeasureCenterSize() override {
            if (Content) return Content->MeasureCenterSize();
            return { };
        }
    };

    // TODO: Add _Content member
    struct Builder : UIElement
    {
        Func<Index::UI::UIElement*()> BuildFunc;
        INDEX_UI_NEW_CLASS(Builder, Func<Index::UI::UIElement*()> BuildFunc;);
        INDEX_UI_NEW_CONSTRUCTOR(Builder) {
            BuildFunc = e.BuildFunc;
        }
        void Build(Layout i) override {
            if (BuildFunc) {
                auto c = BuildFunc();
                if (c) c->Build(i);
            }
        }
        void Notify(INotification* e) override {
            if (BuildFunc) {
                auto c = BuildFunc();
                if (c) c->Notify(e);
            }
        }
    };

    // TODO: Add _Content member
    struct StatefulBuilder : UIElement, IRenderState
    {
        Func<Index::UI::UIElement*()> BuildFunc;
        INDEX_UI_NEW_CLASS(StatefulBuilder, Func<Index::UI::UIElement*()> BuildFunc;);
        INDEX_UI_NEW_CONSTRUCTOR(StatefulBuilder) {
            BuildFunc = e.BuildFunc;
        }
        void Build(Layout i) override {
            (+UIContext::CurrentStates)->AddState(static_cast<IRenderState*>(this));
            if (!UIContext::RebuildTree) return;
            this->ClearRenderList();
            if (BuildFunc) {
                auto c = BuildFunc();
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
            if (BuildFunc) {
                auto c = BuildFunc();
                if (c) c->Notify(e);
            }
        }
    };

    struct NextElement : UIElement {
        List<IPtr<UIElement>> Content;
        INDEX_UI_NEW_CLASS(NextElement, List<IPtr<UIElement>> Content;);
        INDEX_UI_NEW_CONSTRUCTOR(NextElement) {
            Content = std::move(e.Content);
        }
        void Build(Layout i) override {
            for (auto& c : Content) {
                if (c) c->Build(i);
            }
        }
        void Notify(INotification* e) override {
            for (auto& c : Content) {
                Notify(e);
                if (e->Handled) return;
            }
        }
        LayoutInfo MeasureCenterSize() override {
            return LayoutInfo::FromList(Content);
        }
    };

    struct Element : UIElement
    {
    private:
        IPtr<NextElement> _Next;
        List<IPtr<UIElement>> _Content;
    public:
        IPtr<UIElement> GetNewNext() {
            _Next = NextElement::New();
            return _Next;
        }
        void SetNextContent(IPtr<UIElement> c) {
            if (c.IsNull) return;
            if (_Next) {
                _Next->Content.Add(std::move(c));
            }
        }
        __declspec(property(get = GetNewNext, put = SetNextContent)) IPtr<UIElement> next;
        void AddContent(IPtr<UIElement> c) {
            _Content.Add(std::move(c));
        }
        __declspec(property(put = AddContent)) IPtr<UIElement> add;
        List<IPtr<UIElement>>& GetContent() {
            return _Content;
        }
        __declspec(property(get = GetContent)) List<IPtr<UIElement>>& Content;
    public:
        virtual void Construct() = 0;
        void Build(Layout i) override {
            GetNewNext();
            _Content.Clear();
            Construct();
            for (auto& c : _Content) {
                if (c) c->Build(i);
            }
        }
        void Notify(INotification* e) override {
            for (auto& c : _Content) {
                if (c) c->Notify(e);
                if (e->Handled) return;
            }
        }
    };

    struct StatefulElement : UIElement, IRenderState
    {
    private:
        IPtr<NextElement> _Next;
        List<IPtr<UIElement>> _Content;
    public:
        IPtr<UIElement> GetNewNext() {
            _Next = NextElement::New();
            return _Next;
        }
        void SetNextContent(IPtr<UIElement> c) {
            if (c.IsNull) return;
            if (_Next) {
                _Next->Content.Add(std::move(c));
            }
        }
        __declspec(property(get = GetNewNext, put = SetNextContent)) IPtr<UIElement> next;
        void AddContent(IPtr<UIElement> c) {
            _Content.Add(std::move(c));
        }
        __declspec(property(put = AddContent)) IPtr<UIElement> add;
        List<IPtr<UIElement>>& GetContent() {
            return _Content;
        }
        __declspec(property(get = GetContent)) List<IPtr<UIElement>>& Content;
    public:
        virtual void Construct() = 0;
        void Build(Layout i) override {
            (+UIContext::CurrentStates)->AddState(static_cast<IRenderState*>(this));
            if (!UIContext::RebuildTree) return;
            this->ClearRenderList();
            GetNewNext();
            _Content.Clear();
            Construct();
            for (auto& c : _Content) {
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
            for (auto& c : _Content) {
                if (c) c->Notify(e);
                if (e->Handled) return;
            }
        }
    };
}

// Layout Elements
namespace Index::UI
{
    struct StackH : UIElement
    {
        List<IPtr<UIElement>> Content;
        INDEX_UI_NEW_CLASS(StackH, INDEX_UI_DEFAULT_NEW_MEBERS; List<IPtr<UIElement>> Content;);
        INDEX_UI_NEW_CONSTRUCTOR(StackH) {
            INDEX_UI_SET_DEFAULT_MEMBERS;
            Content = std::move(e.Content);
        }
        void Build(Layout i) override {
            auto ci = MeasureCenterSize();
            Rect r = AlignContentRect(i, ci.Size, {
                FloatValueOr(0, Size.Width, MinSize.Width),
                FloatValueOr(0, Size.Height, MinSize.Height)
            });
            float& x = r.X;
            for (auto& c : Content) {
                if (c.IsNull) continue;
                auto ci2 = c->MeasureCenterSize();
                c->Build({
                    .Area {
                        x, r.Y,
                        ci2.Width, r.Height
                    }
                });
                x += ci2.Width;
            }
        }
        void Notify(INotification* e) override {
            for (auto& c : Content) {
                Notify(e);
                if (e->Handled) return;
            }
        }
        LayoutInfo MeasureCenterSize() override {
            LayoutInfo i {
                .Size {
                    FloatValueOr(Size.Width, MinSize.Width, 0),
                    FloatValueOr(Size.Height, MinSize.Height, 0)
                }
            };
            float& w = i.Size.Width, h = i.Size.Height;
            float nw = 0;
            for (auto& c : Content) {
                if (!c) continue;
                auto info = c->MeasureCenterSize();
                if (info.Width != NullF) {
                    nw += info.Width;
                }
                if (info.Height != NullF) {
                    if (info.Height >= (h == NullF ? 0 : h)) {
                        h = info.Height;
                    }
                }
            }
            w = Max(nw, w);
            return {
                .Size {
                    Min(w, MaxSize.Width),
                    Min(h, MaxSize.Height),
                }
            };
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