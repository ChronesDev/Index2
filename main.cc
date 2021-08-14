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
        add = StackV n {{
            .Size { 100, NullF },
            alignment Center,
            content {
                INew<Index::UI::ImUI::Rectangle>(Index::UI::ImUI::Rectangle::Args {
                    .Size { NullF, 10 },
                    .Fill = Colors::Black
                }),
                INew<Index::UI::ImUI::Rectangle>(Index::UI::ImUI::Rectangle::Args {
                    .Size { NullF, 30 },
                    .Fill = Colors::Blue
                }),
                INew<Index::UI::ImUI::Rectangle>(Index::UI::ImUI::Rectangle::Args {
                    .Size { NullF, 10 },
                    .Fill = Colors::Orange
                }),
                INew<Index::UI::ImUI::Rectangle>(Index::UI::ImUI::Rectangle::Args {
                    .Size { NullF, 10 },
                    .Fill = Colors::Black
                }),
                INew<Index::UI::ImUI::Rectangle>(Index::UI::ImUI::Rectangle::Args {
                    .Size { NullF, 30 },
                    .Fill = Colors::Blue
                }),
                INew<Index::UI::ImUI::Rectangle>(Index::UI::ImUI::Rectangle::Args {
                    .Size { NullF, 10 },
                    .Fill = Colors::Orange
                }),
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

        UIContext::Root->Rebuild({
            .Area = Rect { 0, 0, WindowSize }
        });

        // Background
        db.AddRectFilled({0, 0}, {WindowSize.X, WindowSize.Y}, ToImColor(Colors::White));

        UIContext::Render();

    };

    Entry();


    return 0;
}

#include <index_ui_macros_end>