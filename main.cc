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
    UPtr<ImUI::ImUIContext> context = UNew<ImUI::ImUIContext>();

    auto a = UI::Stack n ({
        StackV n ({
            .Alignment = Align::Center,
            content {
                FixedGrid n (Index::UI::FixedGrid::Args {
                    .Size { 300, 140 },
                    .Columns = 3,
                    .Rows = 1,
                    content {
                        FixedGridElement n ({
                            .Column = 2,
                            .Row = 0,
                            content {
                                ImUI::FillRect n ({
                                    .Fill = Colors::Blue
                                })
                            }
                        }),
                        FixedGridElement n ({
                            .Column = 0,
                            .Row = 0,
                            .ColumnSpan = 2,
                            content {
                                ImUI::FillRect n ({
                                    .Fill = Colors::Red
                                })
                            }
                        })
                    }
                }),
                ImUI::FillRect n ({
                    .MinSize { 0, 20 },
                    .Fill = Colors::Green
                })
            }
        })
    });

    context->SetRoot(a);

    OnRender = [&]() {

        ImDrawList& db = *ImGui::GetBackgroundDrawList();
        db.AddRect({0, 0}, ToImVec2(WindowSize),ToImColor(Colors::Blue));

        context->Render(WindowSize, &db);

    };

    Entry();


    return 0;
}

#include <index_ui_macros_end>