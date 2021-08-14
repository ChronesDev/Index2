#pragma once

#include <iostream>
#include <imgui.h>
#include "../ui.cc"
#include "../ui_std.cc"

namespace Index::UI
{
    inline ImColor ToImColor(Color color) { return ImColor(color.R, color.G, color.B, color.A); }
    inline ImVec2 ToImVec2(Vec2F vector) { return ImVec2(vector.X, vector.Y); }
    inline ImVec4 ToImVec4(Vec4F vector) { return ImVec4(vector.X, vector.Y, vector.Z, vector.W); }
}

namespace Index::UI::UIContext
{
    inline ImDrawList* DrawList;
}

namespace Index::UI::ImUI
{
    struct WindowRoot : public State
    {
        Index::Size WindowSize { 1920, 1080 };
        struct New
        {
            Index::Size WindowSize;
            List <IPtr<UIElement>> Content;
            operator Index::IPtr<Index::UI::UIElement>()
            {
                return std::static_pointer_cast<Index::UI::UIElement>(
                    Index::INew<WindowRoot>(*this));
            }
            operator Index::IPtr<State>()
            {
                return std::static_pointer_cast<State>(
                    Index::INew<WindowRoot>(*this));
            }
            operator Index::IPtr<WindowRoot>() { return Index::INew<WindowRoot>(*this); }
        };
        INDEX_UI_NEW_CONSTRUCTOR_ARGS(WindowRoot, New) {
            WindowSize = e.WindowSize;
            Content = std::move(e.Content);
        }
        void Build(Layout i) override {
            Index::UI::UIContext::CurrentStates += this;
            if (!UIContext::RebuildTree) return;
            this->ClearRenderList();
            for (auto& c : Content) {
                if (c) c->Build(i);
            }
        }
    };

    struct Rectangle : UIElement
    {
        Color Fill;
        INDEX_UI_ARGS {
            INDEX_UI_DEFAULT_NEW_MEBERS;
            Color Fill;
        };
        INDEX_UI_NEW_CLASS(Rectangle);
        INDEX_UI_NEW_CONSTRUCTOR(Rectangle) {
            INDEX_UI_SET_DEFAULT_MEMBERS;
            Fill = e.Fill;
        }
        void Build(Layout i) override {
            auto fill = Fill;
            auto r = LayoutUtils::CalculateUIElementSubrect(this, i);
            INDEX_UI_THISSTATE->RenderList.Add([fill, r]{
                UIContext::DrawList->AddRectFilled(ToImVec2(r.First), ToImVec2(r.Second), ToImColor(fill));
            });
        }
        void Notify(INotification* e) override { }
    };
}