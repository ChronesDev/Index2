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
        Index::Color Color;
        ImDrawFlags Flags = ImDrawFlags_None;
        INDEX_UI_Args {
            INDEX_UI_DefaultMembers
            Index::Color Color;
            ImDrawFlags Flags = ImDrawFlags_None;
        };
        INDEX_UI_New(FillRect)
        INDEX_UI_Constructor(FillRect) {
            INDEX_UI_SetDefaultMembers
            Color = e.Color;
            Flags = e.Flags;
        }
        void Render(UIContext* u, Layout i) override {
            auto r = GetSubrect(this, i);
            ImUIContext::DrawList->AddRectFilled(ToImVec2(r.First), ToImVec2(r.Second), ToImColor(Color), 0, Flags);
        }
        void Notify(UINotification* e) override { }
        Index::Size MeasureIntentSize(Layout i) override {
            auto s = UIElement::MeasureIntentSize(i);
            return s;
        }
    };

    struct OutRect : UIElement
    {
        Index::Color Color;
        float Thickness = 1;
        ImDrawFlags Flags = ImDrawFlags_None;
        INDEX_UI_Args {
            INDEX_UI_DefaultMembers
            Index::Color Color;
            float Thickness = 1;
            ImDrawFlags Flags = ImDrawFlags_None;
        };
        INDEX_UI_New(OutRect)
        INDEX_UI_Constructor(OutRect) {
            INDEX_UI_SetDefaultMembers
            Color = e.Color;
            Thickness = e.Thickness;
            Flags = e.Flags;
        }
        void Render(UIContext* u, Layout i) override {
            auto r = GetSubrect(this, i);
            ImUIContext::DrawList->AddRect(ToImVec2(r.First), ToImVec2(r.Second), ToImColor(Color), 0, Flags, Thickness);
        }
        void Notify(UINotification* e) override { }
        Index::Size MeasureIntentSize(Layout i) override {
            auto s = UIElement::MeasureIntentSize(i);
            return s;
        }
    };

    struct FillRRect : UIElement
    {
        Index::Color Color;
        float Rounding = 0.0f;
        ImDrawFlags Flags = ImDrawFlags_None;
        INDEX_UI_Args {
            INDEX_UI_DefaultMembers
            Index::Color Color;
            float Rounding = 0.0f;
            ImDrawFlags Flags = ImDrawFlags_None;
        };
        INDEX_UI_New(FillRRect)
        INDEX_UI_Constructor(FillRRect) {
            INDEX_UI_SetDefaultMembers
            Color = e.Color;
            Rounding = e.Rounding;
            Flags = e.Flags;
        }
        void Render(UIContext* u, Layout i) override {
            auto r = GetSubrect(this, i);
            ImUIContext::DrawList->AddRectFilled(ToImVec2(r.First), ToImVec2(r.Second), ToImColor(Color), Rounding, Flags);
        }
        void Notify(UINotification* e) override { }
        Index::Size MeasureIntentSize(Layout i) override {
            auto s = UIElement::MeasureIntentSize(i);
            return s;
        }
    };

    struct OutRRect : UIElement
    {
        Index::Color Color;
        float Thickness = 1;
        float Rounding = 0.0f;
        ImDrawFlags Flags = ImDrawFlags_None;
        INDEX_UI_Args {
            INDEX_UI_DefaultMembers
            Index::Color Color;
            float Thickness = 1;
            float Rounding = 0.0f;
            ImDrawFlags Flags = ImDrawFlags_None;
        };
        INDEX_UI_New(OutRRect)
        INDEX_UI_Constructor(OutRRect) {
            INDEX_UI_SetDefaultMembers
            Color = e.Color;
            Thickness = e.Thickness;
            Rounding = e.Rounding;
            Flags = e.Flags;
        }
        void Render(UIContext* u, Layout i) override {
            auto r = GetSubrect(this, i);
            ImUIContext::DrawList->AddRect(ToImVec2(r.First), ToImVec2(r.Second), ToImColor(Color), Rounding, Flags, Thickness);
        }
        void Notify(UINotification* e) override { }
        Index::Size MeasureIntentSize(Layout i) override {
            auto s = UIElement::MeasureIntentSize(i);
            return s;
        }
    };
}