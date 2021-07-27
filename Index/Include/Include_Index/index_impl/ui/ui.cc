#pragma once

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <variant>

#include "../core/include.cc"
#include "../std/include.cc"

namespace Index::UI
{
    struct IRenderState;
    struct UIElement;
    struct State;
}

/// Values
namespace Index::UI::UIContext
{
    extern bool RebuildTree;
    extern IPtr<State> Root;
    extern Stack<IRenderState*> CurrentStates;
}

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
        void AddCommand(IRenderCommand command) {
            RenderList.Push(command);
        }
        void AddState(IRenderState* state) {
            if (!state) return;
            RenderList.Push(state);
        }
    };
}

namespace Index::UI
{
    struct UIElement
    {
        virtual void Build() = 0;
    };

    struct State : UIElement, IRenderState
    {
        List<IPtr<UIElement>> Content;
        void Build() override {
            (+UIContext::CurrentStates)->AddState(static_cast<IRenderState*>(this));
            for (auto& c : Content) {
                if (c) c->Build();
            }
        }
        void Rebuild() {
            bool isRebuilding = Index::UI::UIContext::RebuildTree;
            Index::UI::UIContext::RebuildTree = true;
            Build();
            Index::UI::UIContext::RebuildTree = isRebuilding;
        }
    };
}

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

// HERE

namespace Index::UI
{
    struct Empty : UIElement
    {
        NEW_CLASS(Empty,);
        NEW_CONSTRUCTOR(Empty) { }
        void Build() override { }
    };

    struct Builder : UIElement
    {
        Func<Index::UI::UIElement*()> BuildFunc;
        NEW_CLASS(Builder, Func<Index::UI::UIElement*()> BuildFunc;);
        NEW_CONSTRUCTOR(Builder) {
            BuildFunc = e.BuildFunc;
        }
        void Build() override {
            if (BuildFunc) {
                auto c = BuildFunc();
                if (c) c->Build();
            }
        }
    };

    struct StatefulBuilder : UIElement, IRenderState
    {
        Func<Index::UI::UIElement*()> BuildFunc;
        NEW_CLASS(StatefulBuilder, Func<Index::UI::UIElement*()> BuildFunc;);
        NEW_CONSTRUCTOR(StatefulBuilder) {
            BuildFunc = e.BuildFunc;
        }
        void Build() override {
            if (!UIContext::RebuildTree) return;
            if (BuildFunc) {
                auto c = BuildFunc();
                if (c) c->Build();
            }
        }
        void Rebuild() {
            bool isRebuilding = Index::UI::UIContext::RebuildTree;
            Index::UI::UIContext::RebuildTree = true;
            Build();
            Index::UI::UIContext::RebuildTree = isRebuilding;
        }
    };

    struct NextElement : UIElement {
        List<IPtr<UIElement>> Content;
        NEW_CLASS(NextElement, List<IPtr<UIElement>> Content;);
        NEW_CONSTRUCTOR(NextElement) {
            Content = std::move(e.Content);
        }
        void Build() override {
            for (auto& c : Content) {
                if (c) c->Build();
            }
        }
    };

    struct Element : UIElement
    {
    private:
        IPtr<NextElement> _Next;
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
    public:
        virtual void Construct() = 0;
        void Build() override {
            GetNewNext();
            Construct();
        }
    };

    struct StatefulElement : UIElement, IRenderState
    {

    };
}

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

#pragma clang diagnostic pop