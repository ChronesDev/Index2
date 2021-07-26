#include <iostream>
#include <chrono>
#include <index>

#include "src/Window.h"

#include <index_ui_macros>

#define n ::New

int main()
{
    using namespace Index;
    using namespace Index::UI;

    OnRender = []() {

        (+Index::UI::UIContext::CurrentStates)->AddCommand([]{
            ui_ref r = Builder n {[]{
                return nullptr;
            }};
        });

    };

    Entry();

    return 0;
}

#include <index_ui_macros_end>