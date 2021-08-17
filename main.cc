#include <iostream>
#include <chrono>
#include <any>
#include <index>

#include "src/Window.h"

#include <index_ui_macros>

#define n ::New
#define u .UIRef

using namespace Index;
using namespace Index::UI;

int main()
{


    OnRender = []() {

        ImDrawList& db = *ImGui::GetBackgroundDrawList();
        //UIContext::DrawList = ImGui::GetForegroundDrawList();



    };

    Entry();


    return 0;
}

#include <index_ui_macros_end>