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
    e.MinWidth = 100;
    e.PaddingLeft = 11;
    var padding = e.PaddingOr(0);
    e.Id = "11";
    e.Name = "11";
    var& children = e.Children;
    {
    }

    Console.ReadLine();
}

#include <index_macros_end>
#include <index_ui_macros_end>