#include <iostream>
#include <chrono>
#include <index>

#include "src/Window.h"

#include <index_ui_macros>

int main()
{
    OnRender = []() {

        using namespace Index;
        using namespace Index::UI;
        using namespace Index::UI::ImUI;

        var size = WindowSize;
        var e = RenderContext {
            .Render = *(ImGui::GetForegroundDrawList()),
            .ForegroundRender = *(ImGui::GetForegroundDrawList()),
            .BackgroundRender = *(ImGui::GetBackgroundDrawList())
        };
        var i = RenderInfo {
            .Area = Rect {
                0, 0, size.X, size.Y
            }
        };

        var render = Stack::New({
            Rectangle::New({
                .Fill = Colors::Lime
            })
        });

        render->Render(e, i);

    };

    Entry();

    return 0;
}

#include <index_ui_macros_end>