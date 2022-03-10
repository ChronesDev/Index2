#pragma once

#include "../../index.cc"

namespace Index::UI
{
    struct IUIRoot : IObj<IUIRoot>
    {
    public:
        virtual ~IUIRoot() = default;
    };
}