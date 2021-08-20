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

namespace Index::UI::ImUI
{
    struct ImUIContext : UIContext
    {
        ImUIContext() {

        }
        ~ImUIContext() {

        }

        inline static bool IsRendering;
        inline static ImDrawList* DrawList;

        std::chrono::high_resolution_clock Clock;
        std::chrono::time_point<std::chrono::high_resolution_clock, TimeSpan> LastRenderTimePoint = Clock.now();

        inline void Render(Size screenSize, ImDrawList* drawList) {
            // Check if it is already being rendered
            if (IsRendering) throw "UI is already rendering.";
            IsRendering = true;

            // Setup DrawList
            DrawList = drawList;

            // Setup DeltaTime
            auto now = Clock.now();
            DeltaTime = now - LastRenderTimePoint;
            LastRenderTimePoint = now;

            // Check if Root is null
            if (Root.IsNull) throw "Root was null.";

            // Render
            Root->Render(this, {
                .Area = {
                    0, 0, screenSize
                }
            });

            // Set IsRendering to false
            IsRendering = false;
        }
        inline void Notify(UINotification* e) override {
            if (e == nullptr) throw "e was nullptr.";
            if (Root.IsNull) throw "Root was null.";
            Root->Notify(e);
        }
    };
}

namespace Index::UI::ImUI
{
    struct FillRect : UIElement
    {
        Color Fill;
        INDEX_UI_Args {
            INDEX_UI_DefaultMembers
            Color Fill;
        };
        INDEX_UI_New(FillRect)
        INDEX_UI_Constructor(FillRect) {
            INDEX_UI_SetDefaultMembers
            Fill = e.Fill;
        }
        void Render(UIContext* u, Layout i) override {
            auto r = GetSubrect(this, i);
            ImUIContext::DrawList->AddRectFilled(ToImVec2(r.First), ToImVec2(r.Second), ToImColor(Fill));
        }
        void Notify(UINotification* e) override { }
        Index::Size MeasureIntentSize(Layout i) override {
            auto s = UIElement::MeasureIntentSize(i);
            return s;
        }
    };
}