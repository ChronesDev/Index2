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
                    .Size { NullF, 20 },
                    .Fill = Colors::Orange
                }),
                INew<Index::UI::ImUI::Rectangle>(Index::UI::ImUI::Rectangle::Args {
                    .Size { NullF, 20 },
                    .Fill = Colors::Lime
                }),
                INew<Index::UI::ImUI::Rectangle>(Index::UI::ImUI::Rectangle::Args {
                    .Size { NullF, 20 },
                    .Fill = Colors::White
                }),
            }
        }};
        add = StackV n {{
            .Size { 100, NullF },
            alignment LeftTop,
            content {
                INew<Index::UI::ImUI::Rectangle>(Index::UI::ImUI::Rectangle::Args {
                    .Size { NullF, 100 },
                    .Fill = Colors::Yellow
                }),
            }
        }};
        add = StackV n {{
            .Size { 100, NullF },
            alignment RightTop,
            content {
                INew<Index::UI::ImUI::Rectangle>(Index::UI::ImUI::Rectangle::Args {
                    .Size { NullF, 50 },
                    .Fill = Colors::Red
                }),
            }
        }};
        add = StackV n {{
            alignment Bottom,
            content {
                INew<Index::UI::ImUI::Rectangle>(Index::UI::ImUI::Rectangle::Args {
                    .Size { NullF, 5 },
                    .Fill = Colors::Red
                }),
            }
        }};
        add = StackV n {{
            .Size { 100, NullF },
            alignment BottomCenter,
            content {
                INew<Index::UI::ImUI::Rectangle>(Index::UI::ImUI::Rectangle::Args {
                    .Size { NullF, 40 },
                    .Fill = Colors::Aqua
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
        db.AddRectFilled({0, 0}, {WindowSize.X, WindowSize.Y}, ToImColor(Colors::Black));

        UIContext::Render();

    };

    Entry();


    return 0;
}

#include <index_ui_macros_end>