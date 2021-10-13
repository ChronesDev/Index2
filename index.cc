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

void f()
{

}

int main()
{
    Index::Event<void()> e;
    auto a = e.Subscribers;
    for (auto& v : e)
    {
        v();
    }
    Index::Console::LogF("Hello {0}\n{1}", "World", e.Subscribers.Length);
}