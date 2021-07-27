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

    UIContext::BeginBuild();

    struct Button : Element
    {
        bool isHovered = false;
        void Construct() override {
            ui_self_init;
            add = Holder n {
                content {
                    next
                }
            };

            next = Holder n { };
            next = Holder n { };
        }
    };

    UIContext::EndBuild();

    OnRender = []() {

        UIContext::Render();

    };

    Entry();

    return 0;
}

#include <index_ui_macros_end>