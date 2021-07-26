#pragma once

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <variant>
#include <imgui.h>

#include "../core/include.cc"
#include "../std/include.cc"

namespace Index::UI
{
    inline ImColor ToImColor(Color color) { return ImColor(color.R, color.G, color.B, color.A); }
    inline ImVec2 ToImVec2(Vec2F vector) { return ImVec2(vector.X, vector.Y); }
    inline ImVec4 ToImVec4(Vec4F vector) { return ImVec4(vector.X, vector.Y, vector.Z, vector.W); }
}

namespace Index::UI
{
    struct IRenderState;
    struct UIElement;
}

namespace Index::UI::RenderContext
{
    // Values
    extern bool RebuildTree;
    extern Stack<IRenderState*> CurrentStates;
    extern Stack<Rect> ContentArea;
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
            (+RenderContext::CurrentStates)->AddState(static_cast<IRenderState*>(this));
            for (auto& c : Content) {
                if (c) {
                    c->Build();
                }
            }
        }
        void Rebuild() {
            namespace context = RenderContext;
            bool isRebuilding = context::RebuildTree;
            context::RebuildTree = true;
            Build();
            context::RebuildTree = isRebuilding;
        }
    };
}

#define NEW_CLASS(class_name, properties) struct New {                                  \
    properties                                                                          \
    operator Index::IPtr<UIElement>() {                                                 \
        return std::static_pointer_cast<UIElement>(Index::INew<class_name>(*this));     \
    }                                                                                   \
    operator Index::IPtr<class_name>() {                                                \
        return Index::INew<class_name>(*this);                                          \
    }                                                                                   \
};

#define NEW_CONSTRUCTOR(class_name) explicit class_name(New e)

#define ThisState (+Index::UI::RenderContext::CurrentStates)

// HERE

namespace Index::UI
{
    struct Rectangle : UIElement
    {
        NEW_CLASS(Rectangle, );
        NEW_CONSTRUCTOR(Rectangle) {

        }
        void Build() override {
            ThisState->AddCommand([]{
                ImGui::GetForegroundDrawList()->AddRect({0,0}, {10,10}, ToImColor(Colors::Lime));
            });
        }
    };
}

#undef NEW_CLASS
#undef NEW_CONSTRUCTOR
#undef ThisState

namespace Index::UI::RenderContext
{
    // Values
    inline bool RebuildTree = true;
    inline Stack<IRenderState*> CurrentStates;
    inline Stack<Rect> ContentArea;
}
#pragma clang diagnostic pop