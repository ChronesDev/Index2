#include <iostream>
#include <chrono>
#include <any>
#include <index>

#include "src/Window.h"

#include <index_ui_macros>

#define n ::New
#define u .UIRef
#define null NullF

using namespace Index;
using namespace Index::UI;


int main()
{

    UPtr<ImUI::ImUIContext> context = UNew<ImUI::ImUIContext>();

    auto ui = UI::Stack n ({
        StackV n ({
            alignment Center,
            content {
                Container n ({
                    .MinSize { 400, 400 },
                    content {
                        Dock n ({
                            .FillLast = true,
                            content {
                                Dock::Left({
                                    ImUI::FillRect n ({
                                        .MinSize { 50, null },
                                        .Fill = Colors::Red
                                    })
                                }),
                                Dock::Top({
                                    ImUI::FillRect n ({
                                        .MinSize { null, 50 },
                                        .Fill = Colors::Blue
                                    })
                                }),
                                Dock::Right({
                                    ImUI::FillRect n ({
                                        .MinSize { 50, null },
                                        .Fill = Colors::Pink
                                    })
                                }),
                                Dock::Fill({
                                    ImUI::FillRect n ({
                                        .Fill = Colors::Aqua
                                    })
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
        db.AddRectFilled({0, 0}, ToImVec2(WindowSize),ToImColor(Colors::Black));

        context->Render(WindowSize, &db);

    };

    Entry();


    return 0;
}

#include <index_ui_macros_end>