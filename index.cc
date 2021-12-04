#include <index>
#include <index_ui>

int main()
{
    using namespace Index;

    auto a = LinearAnimation { 0, 10, TimeSpan::FromSec(8) };

    a.Start();
    while (a.IsPlaying)
    {
        Console.WriteLine("Value: ", a.Value);
    }
    a.Stop();


}