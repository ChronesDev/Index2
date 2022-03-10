#pragma once

#include "../element/element.cc"

namespace Index::UI
{
    struct UIScope : virtual UIElement, virtual IUIScope
    {
    public:
        ~UIScope() override = default;
    };
}