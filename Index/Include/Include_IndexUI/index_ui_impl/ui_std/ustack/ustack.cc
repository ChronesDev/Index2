#pragma once

#include "../ui.cc"
#include "../container/container.cc"

namespace Index::UI
{
    INDEX_UI_Declare(UStack);

    struct UStack : virtual UIContainer
    {
        INDEX_UI_UseMapper(UStackMapper);

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

    struct UStackMapper : virtual UIContainerMapper
    {
        INDEX_UI_Ref Make() override
        {
            IPtr<UStack> e_ref = INew<UStack>();
            UStack& e = e_ref.Value;

            Impl_(e);
            Impl_Children_(e);

            return e_ref.DynamicAs<UIElement>();
        }
    };
}