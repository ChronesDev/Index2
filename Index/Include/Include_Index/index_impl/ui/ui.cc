#pragma once

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
    class RenderContext
    {
    public:
        ImDrawList& Render;
        ImDrawList& ForegroundRender;
        ImDrawList& BackgroundRender;
    };

    struct LayoutInfo
    {
        Nullable<Size> Size = Null;
    };

    struct RenderInfo
    {
        Rect Area;
        Vec2F GetSize() const { return { Area.Width, Area.Height }; };
        Vec2F GetStart() const { return { Area.X, Area.Y }; };
        Vec2F GetEnd() const { return { Area.X + Area.Width, Area.Y + Area.Height }; };
        __declspec(property(get = GetSize)) Vec2F Size;
        __declspec(property(get = GetStart)) Vec2F Start;
        __declspec(property(get = GetEnd)) Vec2F End;
        RenderInfo ContentArea(Vec4F padding) {
            return RenderInfo{
                .Area = Rect {
                    Area.X + std::min(padding.X, Size.X / 2),
                    Area.Y + std::min(padding.Y, Size.Y / 2),
                    Area.Width - std::min(padding.Z, Size.X / 2),
                    Area.Height - std::min(padding.W, Size.Y / 2)
                }
            };
        }
    };

    struct UIElement
    {
        virtual LayoutInfo Render(RenderContext& e, RenderInfo i) = 0;
    };

    struct Builder : public UIElement
    {
        Func<UIElement*()> Build = nullptr;
        Builder() = default;
        explicit Builder(Func<UIElement*()> e) {
            Build = std::move(e);
        }
        template<class T = UIElement, class... Args> static IPtr<T> New(Args&&... args) {
            if constexpr (std::is_same<T, Builder>::value) return INew<Builder>(std::forward<Args>(args)...);
            else return std::static_pointer_cast<T>(INew<Builder>(std::forward<Args>(args)...));
        }
        LayoutInfo Render(RenderContext& e, RenderInfo i) override {
            if (Build) {
                UIElement* element = Build();
                if (element) {
                    return element->Render(e, i);
                }
            }
            return LayoutInfo {
                .Size = i.Size
            };
        }
    };

    struct Stack : public UIElement
    {
        List<IPtr<UIElement>> Content;
        explicit Stack(List<IPtr<UIElement>> e) {
            Content = std::move(e);
        }
        template<class T = UIElement> static IPtr<T> New(List<IPtr<UIElement>> e) {
            if constexpr (std::is_same<T, Stack>::value) return INew<Stack>(e);
            else return std::static_pointer_cast<T>(INew<Stack>(e));
        }
        LayoutInfo Render(RenderContext& e, RenderInfo i) override {
            for(auto& ui : Content) {
                if (!ui.IsNull) {
                    ui->Render(e, i);
                }
            }
            return LayoutInfo {
                .Size = i.Size
            };
        }
    };
}