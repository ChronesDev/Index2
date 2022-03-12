#pragma once

#include "../../index.cc"

namespace Index::UI
{
    struct IUIScope
    {
    public:
        ~IUIScope() = default;

    public:
        virtual IPtr<UIElement> Scope_Search(UIPath path) = 0;
        virtual IPtr<UIElement> Scope_TrySearch(UIPath path) = 0;
    };
}