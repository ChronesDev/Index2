#include <iostream>
#include <chrono>
#include <any>
#include <index>

#include "src/Window.h"

#include <index_ui_macros>

#define n ::New
#define null Index::UI::NullF
#define size .Size = Index::Size
#define minsize .MinSize = Index::Size
#define maxsize .MaxSize = Index::Size
#define dyn []() -> float
#define selfdyn [](UIDynamic* that, UIContext* u) -> float
#define color .Color =
#define flags .Flags =
#define edges .Edges = Index::Vec4F

using namespace Index;
using namespace Index::UI;

int main()
{
    UPtr<ImUI::ImUIContext> context = UNew<ImUI::ImUIContext>();

    IPtr<UIElement> ui = UI::Stack n ({
        ImUI::FillRect n ({
            color Colors::Transparent
        }),
        Padding n ({
            edges(40, 20),
            content {
                ImUI::OutRRect n ({
                    color Colors::Lime,
                    .Thickness = 10,
                    .Rounding = 11
                }),
                ImUI::ClipContainer n ({
                    size(10, 10),
                    alignment Center,
                    content {
                        ImUI::FillRect n ({
                            size(300, 300),
                            color Colors::Aqua,
                        })
                    }
                })
            }
        })
    });

    context->SetRoot(ui);

    OnRender = [&]() {

        ImDrawList& db = *ImGui::GetBackgroundDrawList();
        db.AddRectFilled({0, 0}, ToImVec2(WindowSize),ToImColor(Colors::Black));

        context->Render(WindowSize, &db);
    };

    Entry();


    return 0;
}

#include <index_ui_macros_end>