#include <index>

namespace Index::UI
{
    // clang-format on
    struct MyControl : ScopedElement<MyControl>
    {
        IPtr<UIElement> Switch_ = Switch::New({
            .Content = {
                Container::New({
                    .Size { 10, 10 },
                }),
                Container::New({
                    .Size { 20, 20 },
                }),
            }
        });

        IPtr<UIElement> Construct() override
        {
            return Container::New({
                .Content = {
                    Executor::New({
                        .Execute = [this](UIContext* u, Layout i) -> void {
                            auto s = Switch_.DynamicAs<Switch>().Ptr;
                            if (s)
                            {
                                s->Index += 1;
                            }
                        }
                    }),
                    Switch_
                }
            });
        }
        // clang-format on
    };
}

int main()
{
    using namespace Index;

    auto now = Time.Now;

    Sleep(2800);
    Console::Log("Here the time: ", TimeSpan::FromHours(20).Minutes);

    Console::LogF("Hello {0}\n", "World");


    auto t = LinearColorTransition(Color::RGB(0, 0, 0), Color::RGB(255, 255, 255));
    Console::Log(t(0.25), " ", t(0.5));
}