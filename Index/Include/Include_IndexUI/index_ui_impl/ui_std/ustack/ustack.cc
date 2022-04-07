#pragma once

#include "../ui.cc"
#include "../container/container.cc"

namespace Index::UI
{
    INDEX_UI_Declare(UStack);

    struct UStack : virtual UIContainer
    {
        INDEX_UI_UseMapper(UStackMapper);
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