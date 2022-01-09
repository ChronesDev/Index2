#pragma once

#include "../container/container.cc"
#include "../ui.cc"

namespace Index::UI
{
    INDEX_UI_Declare(VStack);

    struct VStack : virtual UIContainer
    {
        INDEX_UI_UseMapper(VStackMapper);

        void OnComputeLayoutPosition(Rect i) override
        {
            Rect r = GetSubrect_(i);
            ComputedLayout_ = r;

            float height = 0;
            for (auto& c : Children_)
            {
                Rect r2 = r;
                r2.Y += height;
                r2.Height = c->ComputedMinWidthOr(AutoF);
                c->ComputeLayoutPosition(r2);

                height += c->ComputedMinHeight;
            }

            PolishComputedLayoutPosition();
        }

        void OnComputeLayout() override
        {
            Index::Size minChildren;
            for (auto& c : Children_)
            {
                float width = c->ComputedMinWidth;
                if (minChildren.Width < width) minChildren.Width = width;

                minChildren.Height += c->ComputedMinHeight;
            }

            auto min = ClampSize(ApplyPadding_(minChildren));
            auto max = ActualMaxSize;

            ComputedMinSize_ = ApplyMargin_(min);
            ComputedMaxSize_ = max;

            PolishLayout();
            PolishComputedLayout();
        }
    };

    struct VStackMapper : virtual UIContainerMapper
    {
        INDEX_UI_Ref Make() override
        {
            IPtr<VStack> e_ref = INew<VStack>();
            VStack& e = e_ref.Value;

            Impl_(e);
            Impl_Children_(e);

            return e_ref.DynamicAs<UIElement>();
        }
    };
}