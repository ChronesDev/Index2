#pragma once

#include "../core/include.cc"
#include "../std/include.cc"

namespace Index::UI
{
    class RenderContext
    {
    public:
        // TODO: Finish this
        // ImDrawList& Render;
        // ImDrawList& ForegroundRender;
        // ImDrawList& BackgroundRender;
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
        Builder(Func<UIElement*()> e) {
            Build = std::move(e);
        }
        template<class T = UIElement> static IPtr<T> New() {
            if constexpr (std::is_same<T, Builder>::value) return INew<Builder>();
            else return std::static_pointer_cast<T>(INew<Builder>());
        }
        template<class T = UIElement> static IPtr<T> New(Func<UIElement*()> e) {
            if constexpr (std::is_same<T, Builder>::value) return INew<Builder>(e);
            else return std::static_pointer_cast<T>(INew<Builder>(e));
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
}