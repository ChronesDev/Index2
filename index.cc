#include <index>
#include <index_ui>

int main()
{
    using namespace Index;

    auto now = Time.Now;

    Console.Log(INDEX_CompilerName);

    Console.Log("Here the time: ", TimeSpan::FromHours(20).Minutes, " also: ", now);

    Console.LogF("Hello {0}\n", "World");
    auto console = ConsoleI::New();

    auto t = LinearColorTransition(Color::RGB(0, 0, 0), Color::RGB(255, 255, 255));
    Console.Log(t(0.25), " ", t(0.5));
}