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

    struct MainApp : StatefulElement
    {
        void Construct() override
        {
            ui_list list;
            for (int i = 0; i < 255; i++) {
                list.Add(ImUI::Rectangle n {
                    .Size { 3, 10 },
                    .Fill = Color::RGB(i, i, i)
                });
            }
            add = StackH n {
                .Size { 100, 100 },
                .Alignment = Align::LeftBottom,
                content list
            };
        }
    };

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