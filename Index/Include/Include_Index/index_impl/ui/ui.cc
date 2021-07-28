#pragma once

#include <variant>

#include "../core/include.cc"
#include "../std/include.cc"

// Important
namespace Index::UI
{
    // NullF: The Float value that represents Null
    constexpr float NullF = Limits::FloatMax;
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
        virtual LayoutInfo GetLayoutInfo();
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
        __forceinline void Apply(UIElement* e) {
            Size = { NullF, NullF };
        }
    };
}

// UIElement Implementation
namespace Index::UI
{
    LayoutInfo UIElement::GetLayoutInfo() {
        LayoutInfo i;
        i.Apply(this);
        return i;
    }
}

// State
namespace Index::UI
{
    struct State : UIElement, IRenderState
    {
        List<IPtr<UIElement>> Content;
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

#define DEFAULT_MEMBERS                                          \
Index::Size MinSize { Index::UI::NullF, Index::UI::NullF };     \
Index::Size MaxSize { Index::UI::NullF, Index::UI::NullF };     \
Index::Size Size { Index::UI::NullF, Index::UI::NullF };        \
Index::Align Alignment = Index::Align::Stretch;

#define SET_DEFAULT_MEMBERS     \
this->MinSize = e.MinSize;      \
this->MaxSize = e.MaxSize;      \
this->Size = e.Size;            \
this->Alignment = e.Alignment;


#define NEW_CLASS(class_name, properties) struct New {                                              \
    properties                                                                                      \
    operator Index::IPtr<Index::UI::UIElement>() {                                                  \
        return std::static_pointer_cast<Index::UI::UIElement>(Index::INew<class_name>(*this));      \
    }                                                                                               \
    operator Index::IPtr<class_name>() {                                                            \
        return Index::INew<class_name>(*this);                                                      \
    }                                                                                               \
};

#define NEW_CONSTRUCTOR(class_name) explicit class_name(New e)

#define ThisState (+Index::UI::UIContext::CurrentStates)

// Normal Elements
namespace Index::UI
{
    struct Empty : UIElement
    {
        NEW_CLASS(Empty,);
        NEW_CONSTRUCTOR(Empty) { }
        void Build(Layout i) override { }
        void Notify(INotification* e) override { }
    };

    struct Holder : UIElement
    {
        List<IPtr<UIElement>> Content;
        NEW_CLASS(Holder, List<IPtr<UIElement>> Content;);
        NEW_CONSTRUCTOR(Holder) {
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
        virtual LayoutInfo GetLayoutInfo() {

        }
    };

    struct Wrap : UIElement
    {
        IPtr<UIElement> Content;
        NEW_CLASS(Wrap, IPtr<UIElement> Content;);
        NEW_CONSTRUCTOR(Wrap) {
            Content = std::move(e.Content);
        }
        void Build(Layout i) override {
            if (Content) Content->Build(i);
        }
        void Notify(INotification* e) override {
            if (Content) Content->Notify(e);
        }
        virtual LayoutInfo GetLayoutInfo() {
            LayoutInfo i {
                .Size { MaxSize.Width, MaxSize.Height }
            };
            if (!Alignment.IsHStretched) i.Width = Max(Size.Width, MinSize.Width);
            if (!Alignment.IsVStretched) i.Height = Max(Size.Height, MinSize.Height);
            return i;
        }
    };

    // TODO: Add _Content member
    struct Builder : UIElement
    {
        Func<Index::UI::UIElement*()> BuildFunc;
        NEW_CLASS(Builder, Func<Index::UI::UIElement*()> BuildFunc;);
        NEW_CONSTRUCTOR(Builder) {
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
        NEW_CLASS(StatefulBuilder, Func<Index::UI::UIElement*()> BuildFunc;);
        NEW_CONSTRUCTOR(StatefulBuilder) {
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
        NEW_CLASS(NextElement, List<IPtr<UIElement>> Content;);
        NEW_CONSTRUCTOR(NextElement) {
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
        DEFAULT_MEMBERS;
        List<IPtr<UIElement>> Content;
        NEW_CLASS(StackH, DEFAULT_MEMBERS; List<IPtr<UIElement>> Content;);
        NEW_CONSTRUCTOR(StackH) {
            SET_DEFAULT_MEMBERS;
            Content = std::move(e.Content);
        }
        void Build(Layout i) override {
            if (Alignment.IsHStretched) {

            }
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
    };
}

#undef DEFAULT_MEMBERS
#undef SET_DEFAULT_MEMBERS
#undef NEW_CLASS
#undef NEW_CONSTRUCTOR
#undef ThisState

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