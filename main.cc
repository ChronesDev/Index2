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

struct MainApp : StatefulElement
{
    void Construct() override
    {
        ui_list list;
        add = Container n {{
            .Size { 100, 100 },
            alignment Center,
            content {
                Index::UI::ImUI::Rectangle n {{
                    .Fill = Colors::Pink
                }}
            }
        }};
    }
};

int main()
{
    UIContext::BeginBuild();

    IPtr<UIElement> root = ImUI::WindowRoot n { content {
        INew<MainApp>()
    }};

    UIContext::Root = root.As<State>();

    UIContext::EndBuild();

    OnRender = []() {

        ImDrawList& db = *ImGui::GetBackgroundDrawList();
        UIContext::DrawList = ImGui::GetForegroundDrawList();

        // Background
        db.AddRectFilled({0, 0}, {WindowSize.X, WindowSize.Y}, ToImColor(Colors::Orange));

        UIContext::Render();

    };

    Entry();


    return 0;
}

#include <index_ui_macros_end>