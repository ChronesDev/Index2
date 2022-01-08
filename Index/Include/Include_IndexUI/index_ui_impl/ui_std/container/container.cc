#pragma once

#include "../ui.cc"

// UIContainer
namespace Index::UI
{
    INDEX_UI_Declare(UIContainer);

    struct UIContainer : virtual UIElement
    {
        virtual void Attach(const INDEX_UI_Ref& child) { AttachChild_(child); }
        virtual void Detach(const INDEX_UI_Ref& child) { DetachChild_(child); }
    };

    struct UIContainerMapper : virtual UIMapper
    {
    public:
        template <class T> auto Sub() { return Sub_<T>(); }

    protected:
        template<class T> void Impl_Children_(T& e)
        {
            for (auto& c : Children)
            {
                e.Attach(c->Make());
            }
        }
    };
}

// Container
namespace Index::UI
{
    INDEX_UI_Declare(Container);

    struct Container : virtual UIContainer
    {
        INDEX_UI_UseMapper(ContainerMapper);

        void OnComputeLayoutPosition(Rect i) override
        {
            Rect r = GetSubrect_(i);
            ComputedLayout_ = r;

            float width = 0;
            for (auto& c : Children_)
            {
                Rect r2 = r;
                r2.X += width;
                r2.Width = c->ComputedMinWidthOr(AutoF);
                c->ComputeLayoutPosition(r2);

                width += c->ComputedMinWidth;
            }

            PolishComputedLayoutPosition();
        }

        void OnComputeLayout() override
        {
            auto minChildren = ApplyPadding_(FitRectToChildren_());
            auto min = ClampSize(minChildren);
            auto max = ActualMaxSize;

            ComputedMinSize_ = ApplyMargin_(min);
            ComputedMaxSize_ = max;

            PolishLayout();
            PolishComputedLayout();
        }
    };

    struct ContainerMapper : virtual UIContainerMapper
    {
        INDEX_UI_Ref Make()
        {
            IPtr<Container> e_ref = INew<Container>();
            Container& e = e_ref.Value;

            Impl_(e);
            Impl_Children_(e);

            return e_ref.DynamicAs<UIElement>();
        }
    };
}