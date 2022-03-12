#pragma once

#include "../container/container.cc"

// Container
namespace Index::UI
{
    INDEX_UI_Declare(ScopedContainerMapper);

    struct ScopedContainer : virtual UIScope, virtual UIContainer
    {
        INDEX_UI_UseMapper(ScopedContainerMapper);
    };

    struct ScopedContainerMapper : virtual UIContainerMapper
    {
        INDEX_UI_Ref Make() override
        {
            IPtr<ScopedContainer> e_ref = INew<ScopedContainer>();
            ScopedContainer& e = e_ref.Value;

            Impl_(e);
            Impl_Children_(e);

            return e_ref.DynamicAs<UIElement>();
        }
    };
}