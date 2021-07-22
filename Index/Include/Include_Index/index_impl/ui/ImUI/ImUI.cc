#pragma once

#include "../ui.cc"

namespace Index::UI::ImUI
{
    struct Rectangle : public UIElement
    {
        struct RectangleArgs
        {
            Size Size;
            Vec4F Margin;
            Vec4F Padding;
            Color Fill = Colors::Transparent;
            List<IPtr<UIElement>> Content;
        };
        Size Size;
        Vec4F Margin;
        Vec4F Padding;
        Color Fill = Colors::Transparent;
        List<IPtr<UIElement>> Content;
        Rectangle() = default;
        explicit Rectangle(RectangleArgs e) {
            Size = e.Size;
            Margin = e.Margin;
            Padding = e.Padding;
            Fill = e.Fill;
            Content = std::move(Content);
        }
        template<class T = UIElement> static IPtr<T> New() {
            if constexpr (std::is_same<T, Rectangle>::value) return INew<Rectangle>();
            else return std::static_pointer_cast<T>(INew<Rectangle>());
        }
        template<class T = UIElement> static IPtr<T> New(RectangleArgs e) {
            if constexpr (std::is_same<T, Rectangle>::value) return INew<Rectangle>(e);
            else return std::static_pointer_cast<T>(INew<Rectangle>(e));
        }
        LayoutInfo Render(RenderContext& e, RenderInfo i) override {
            e.Render.AddRectFilled(ToImVec2(i.Start), ToImVec2(i.End), ToImColor(Fill));
            for (auto& c : Content) {
                if (c) c->Render(e, i.ContentArea(Padding));
            }
            return LayoutInfo {
                .Size = Size
            };
        }
    };
}

namespace Index::UI::ImUI
{
    struct OutlineRectangle : public UIElement
    {
        struct OutlineRectangleRectangleArgs
        {
            Size Size;
            Vec4F Margin;
            Vec4F Padding;
            Color Fill = Colors::Transparent;
            List<IPtr<UIElement>> Content;
        };
        Size Size;
        Vec4F Margin;
        Vec4F Padding;
        Color Fill = Colors::Transparent;
        List<IPtr<UIElement>> Content;
        OutlineRectangle() = default;
        explicit OutlineRectangle(OutlineRectangleRectangleArgs e) {
            Size = e.Size;
            Margin = e.Margin;
            Padding = e.Padding;
            Fill = e.Fill;
            Content = std::move(Content);
        }
        template<class T = UIElement> static IPtr<T> New() {
            if constexpr (std::is_same<T, OutlineRectangle>::value) return INew<OutlineRectangle>();
            else return std::static_pointer_cast<T>(INew<OutlineRectangle>());
        }
        template<class T = UIElement> static IPtr<T> New(OutlineRectangleRectangleArgs e) {
            if constexpr (std::is_same<T, OutlineRectangle>::value) return INew<OutlineRectangle>(e);
            else return std::static_pointer_cast<T>(INew<OutlineRectangle>(e));
        }
        LayoutInfo Render(RenderContext& e, RenderInfo i) override {
            e.Render.AddRectFilled(ToImVec2(i.Start), ToImVec2(i.End), ToImColor(Fill));
            for (auto& c : Content) {
                if (c) c->Render(e, i.ContentArea(Padding));
            }
            return LayoutInfo {
                .Size = Size
            };
        }
    };
}

namespace Index::UI::ImUI
{
    struct ClipRect : public UIElement
    {
        struct ClipRectArgs
        {
            Size Size;
            Vec4F Margin;
            Vec4F Padding;
            Color Fill = Colors::Transparent;
            List<IPtr<UIElement>> Content;
        };
        Size Size;
        Vec4F Margin;
        Vec4F Padding;
        Color Fill = Colors::Transparent;
        List<IPtr<UIElement>> Content;
        ClipRect() = default;
        explicit ClipRect(ClipRectArgs e) {
            Size = e.Size;
            Margin = e.Margin;
            Padding = e.Padding;
            Fill = e.Fill;
            Content = std::move(Content);
        }
        template<class T = UIElement> static IPtr<T> New() {
            if constexpr (std::is_same<T, ClipRect>::value) return INew<ClipRect>();
            else return std::static_pointer_cast<T>(INew<ClipRect>());
        }
        template<class T = UIElement> static IPtr<T> New(ClipRectArgs e) {
            if constexpr (std::is_same<T, ClipRect>::value) return INew<ClipRect>(e);
            else return std::static_pointer_cast<T>(INew<ClipRect>(e));
        }
        LayoutInfo Render(RenderContext& e, RenderInfo i) override {
            e.Render.PushClipRect(ToImVec2(i.Start), ToImVec2(i.End), ToImColor(Fill));
            for (auto& c : Content) {
                if (c) c->Render(e, i.ContentArea(Padding));
            }
            e.Render.PopClipRect();
            return LayoutInfo {
                .Size = Size
            };
        }
    };
}