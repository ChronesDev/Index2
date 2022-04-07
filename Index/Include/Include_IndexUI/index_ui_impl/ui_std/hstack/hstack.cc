#pragma once

#include "../container/container.cc"
#include "../ui.cc"

namespace Index::UI
{
    INDEX_UI_Declare(HStack);

    struct HStack : virtual UIContainer
    {
        INDEX_UI_UseMapper(HStackMapper);

        void OnComputeLayoutPosition(Rect i) override
        {
            ComputeComputedLayoutAndContentLayout_(i);
            auto& r = ComputedLayout_;

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
            Index::Size minChildren;
            for (auto& c : Children_)
            {
                float height = c->ComputedMinHeight;
                minChildren.Height = Max(minChildren.Height, height);

                minChildren.Width += c->ComputedMinWidth;
            }

            ComputeComputedSizes_(minChildren);

            PolishLayout();
            PolishComputedLayout();
        }
    };

    struct HStackMapper : virtual UIContainerMapper
    {
        INDEX_UI_Ref Make() override
        {
            IPtr<HStack> e_ref = INew<HStack>();
            HStack& e = e_ref.Value;

            Impl_(e);
            Impl_Children_(e);

            return e_ref.DynamicAs<UIElement>();
        }
    };
}