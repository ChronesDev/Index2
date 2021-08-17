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

    auto ui = UI::Stack n ({
        StackV n ({
            alignment Center,
            content {
                StackH n ({
                    content {
                        ImUI::FillRect n ({
                            .Size { 160, 100 },
                            .Fill = Colors::Blue
                        }),
                        ImUI::FillRect n ({
                            .Size { 160, 100 },
                            .Fill = Colors::Red
                        })
                    }
                }),
                FixedGrid n ({
                    .Size { NullF, 100 },
                    .Columns = 3,
                    content {
                        FixedGridElement n ({
                            .Column = 0,
                            .ColumnSpan = 3,
                            content {
                                ImUI::FillRect n ({
                                    .Fill = Colors::Purple
                                })
                            }
                        }),
                        FixedGridElement n ({
                            .Column = 0,
                            content {
                                ImUI::FillRect n ({
                                    .Fill = Colors::Green
                                })
                            }
                        })
                    }
                })
            }
        })
    });

    context->SetRoot(ui);

    OnRender = [&]() {

        ImDrawList& db = *ImGui::GetBackgroundDrawList();
        db.AddRect({0, 0}, ToImVec2(WindowSize),ToImColor(Colors::Blue));

        context->Render(WindowSize, &db);

    };

    Entry();


    return 0;
}

#include <index_ui_macros_end>