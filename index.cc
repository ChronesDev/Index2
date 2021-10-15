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
    using namespace Index;

    auto a = [] { Console::LogF("@@@ Hello ?"); };
    auto a2 = [] { Console::LogF("@@@ 22222222"); };
    Func<void()> f1 = a;
    Func<void()> f2 = a2;
    Func<void()> f3 = f2;

    Event<void()> e;
    e.Add(a);
    e.Add(f1);
    e.Add(f2);
    e.Add(a2);
    e.Add(f1);
    e.Add(f3);

    Console::LogF("\n###### Round {} ######", 1);
    e.Invoke();
    Console::Log("\n");

    e.Remove(f3);
    Console::LogF("\n###### Round {} ######", 2);
    e.Invoke();
    Console::Log("\n");

    e.RemoveAll(f3);
    Console::LogF("\n###### Round {} ######", 3);
    e.Invoke();
    Console::Log("\n");

    e.RemoveAll(a);
    Console::LogF("\n###### Round {} ######", 4);
    e.Invoke();
    Console::Log("\n");

    Index::Console::LogF("Hello {0}\n", "World");
}