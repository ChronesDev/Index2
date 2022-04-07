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
            ComputeComputedLayoutAndContentLayout_(i);
            auto& r = ComputedLayout_;

            float height = 0;
            for (auto& c : Children_)
            {
                Rect r2 = r;
                r2.Y += height;
                r2.Height = c->ComputedMinHeightOr(AutoF);
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
                minChildren.Width = Max(minChildren.Width, width);

                minChildren.Height += c->ComputedMinHeight;
            }

            ComputeComputedSizes_(minChildren);

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