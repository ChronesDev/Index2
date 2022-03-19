#pragma once

#include "ui/ui_descriptor.h"

#include <index_macros>

namespace Index::UI::ImSDL
{
    struct ImRoot : virtual InputContext, virtual UIRoot
    {
    public:
        union
        {
            ImDrawList* DrawList_;
            ImDrawList* dc;
        };
    };
}

#include <index_macros_end>