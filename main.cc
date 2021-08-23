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
            color Colors::White
        }),
        Padding n ({
            edges(40, 20),
            content {
                ImUI::ShadowRRect n ({
                    color Colors::Black,
                    .Thickness = 30,
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
                }),
                ImUI::ImGuiDemo n ()
            }
        })
    });

    context->SetRoot(ui);

    OnRender = [&]() {

        ImDrawList& db = *ImGui::GetBackgroundDrawList();
        db.AddRectFilled({0, 0}, ToImVec2(WindowSize),ToImColor(Colors::White));

        context->Render(WindowSize, &db);
    };

    Entry();


    return 0;
}

#include <index_ui_macros_end>