#pragma once

#include <type_traits>

#include "../../core/include.cc"
#include "../../std/include.cc"

namespace Index::UI
{
    struct INotification
    {
        bool Handled = false;
        virtual string GetName() = delete;
    };

    struct ICancelable
    {
        bool Cancel = false;
    };
}