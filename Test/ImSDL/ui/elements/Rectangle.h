#pragma once

#include "ui/ui_descriptor.h"
#include "ImRoot.h"

#include <index_macros>

namespace Index::UI::ImSDL
{
    INDEX_UI_Declare(Rectangle);

    struct Rectangle : virtual UIElement
    {
    public:
        INDEX_UI_UseMapper(RectangleMapper);

    public:
        Color Fill;

    protected:
        union
        {
            ImRoot* ImRoot_;
            ImRoot* ir;
        };

    protected:
        void OnAttachedToUIRoot_(IPtr<IUIRoot> root) override
        {
            if (var ptr = dynamic_cast<ImRoot*>(root.Ptr); ptr)
            {
                ImRoot_ = ptr;
            }
            UIElement::OnAttachedToUIRoot_(root);
        }
        void OnDetachedFromUIRoot_() override
        {
            ImRoot_ = nullptr;
            UIElement::OnDetachedFromUIRoot_();
        }

    public:
        void OnRender() override {
            if (!ir) return;

            var& dc = ir->dc;

            dc->AddRectFilled(
                ToImVec(ContentLayout.First),
                ToImVec(ContentLayout.Second),
                ToImColor(Fill));
        }
    };

    struct RectangleMapper : virtual UIElementMapper
    {
    public:
        Color Fill;

    public:
        IPtr<UIElement> Make() override {
            IPtr<Rectangle> e_ref = INew<Rectangle>();
            Rectangle& e = e_ref.Value;

            Impl_(e);
            Impl_Rectangle_(e);

            return e_ref.DynamicAs<UIElement>();
        }

        template <class T> void Impl_Rectangle_(T& e)
        {
            e.Fill = Fill;
        }
    };
}

#include <index_macros_end>