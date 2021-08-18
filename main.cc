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

unsigned __int64 counter = 0;

class A
{
public:
    __int64 i;
    __int64 i2;
    __int64 i3;
    __int64 i4;
    virtual void CallNext(int until, A a1, A a2) {
        if (until <= 0) return;
        counter += 1;
        if (counter == 18446744073709551615 - 10) throw "Limit reached.";
        i = until;
        i2 = until;
        i3 = until;
        i4 = until;
        auto a = A();
        auto a5 = A();
        a.CallNext(until - 1, a5, a);
    }
};

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
                }),
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