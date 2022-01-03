#include <index>
#include <index_ui>

#include <index_macros>
#include <index_ui_macros>

int main()
{
    using namespace Index;

    if (Debug) { Console.Log("Hello World"); }

    Index::UI2::UIElement e;
    e.Width = 100;
    e.AutoMarginTop = true;

    Console.ReadLine();
}

#include <index_macros_end>
#include <index_ui_macros_end>