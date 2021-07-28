#include <iostream>
#include <chrono>
#include <index>

#include "src/Window.h"

#include <index_ui_macros>

#include <memory_resource>

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
            add = Wrap n { next };
            next = Holder n {{

            }};
        }
    };

    UIContext::EndBuild();

    OnRender = []() {

        ImDrawList& d = *ImGui::GetForegroundDrawList();



    };

    Entry();

    return 0;
}

#include <index_ui_macros_end>