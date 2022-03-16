#pragma once

#include "util.h"

#include "key.h"

#include <index_macros>
#include <index_ui_macros>

namespace Index::UI::ImSDL
{
    struct ImSDL_UIInput : UIInputDescriptor
    {
        using TKey = Key;
    };

    using InputContext = UIInputContext<ImSDL_UIInput>;
    using InputElement = UIInputElement<ImSDL_UIInput>;
}

#include <index_ui_macros_end>
#include <index_macros_end>