#include <iostream>
#include <chrono>
#include <any>
#include <index>

#include "src/Window.h"

#include <index_ui_macros>

#define n ::New
#define u .UIRef
#define null NullF
#define size .Size = Size
#define minsize .MinSize = Size
#define maxsize .MaxSize = Size
#define dyn []() -> float

using namespace Index;
using namespace Index::UI;

int main()
{
    UPtr<ImUI::ImUIContext> context = UNew<ImUI::ImUIContext>();

    IPtr<UIElement> ui = UI::Stack n ({
        ImUI::FillRect n ({
            .Fill = Colors::Transparent
        }),
        Container n ({
            minsize(100, 100),
            alignment Center,
            content {
                ImUI::FillRect n ({
                    .Fill = Colors::Red
                })
            }
        })
    });

    context->SetRoot(ui);

    OnRender = [&]() {

        ImDrawList& db = *ImGui::GetBackgroundDrawList();
        db.AddRectFilled({0, 0}, ToImVec2(WindowSize),ToImColor(Colors::Black));

        context->Render(WindowSize, &db);

        std::cout << "DeltaTime: " << context->Delta << std::endl;

    };

    Entry();


    return 0;
}

#include <index_ui_macros_end>