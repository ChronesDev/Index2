#include <iostream>
#include <chrono>
#include <any>
#include <index>

#include "src/Window.h"

#include <index_ui_macros>

#define n ::New
#define null NullF
#define size .Size = Size
#define minsize .MinSize = Size
#define maxsize .MaxSize = Size
#define dyn [&]() -> float
#define selfdyn [](UIDynamic* that, UIContext* u) -> float

using namespace Index;
using namespace Index::UI;

int main()
{
    UPtr<ImUI::ImUIContext> context = UNew<ImUI::ImUIContext>();

    IPtr<UIElement> ui = UI::Stack n ({
        ImUI::FillRect n ({
            .Fill = Colors::Transparent
        }),
        DynContainer n ({
            .DynSize = {
                200, selfdyn {
                    static float i = 30;
                    i += 40 * u->Delta;
                    if (i >= 500) {
                        i = 30;
                    }
                    return i;
                }
            },
            alignment Center,
            content {
                ImUI::FillRect n ({
                    .Fill = Colors::Red,
                })
            }
        }),
    });

    context->SetRoot(ui);

    OnRender = [&]() {

        ImDrawList& db = *ImGui::GetBackgroundDrawList();
        db.AddRectFilled({0, 0}, ToImVec2(WindowSize),ToImColor(Colors::Black));

        std::chrono::high_resolution_clock clock;
        auto start = clock.now();
        context->Render(WindowSize, &db);
        auto now = clock.now();

        static List<std::chrono::nanoseconds> Average;
        auto dur = duration_cast<std::chrono::nanoseconds>((now - start));
        Average.Add(dur);
        if (Average.Length >= 10) {
            auto length = Average.Length;
            long long all = 0;
            for (auto a : Average) {
                all += a.count();
            }
            all /= length;
            std::cout << "Avg: " << all << "ns" << std::endl;
            Average.Clear();
        }
    };

    Entry();


    return 0;
}

#include <index_ui_macros_end>