#include <index>
#include <index_ui>

#include <index_macros>
#include <index_ui_macros>

int main()
{
    using namespace Index;

    if (Debug) { Console.Log("Hello World"); }

    var t = Time.Now;
    Console.Log("Time: ", t);


    Console.ReadLine();
}

#include <index_ui_macros_end>
#include <index_macros_end>