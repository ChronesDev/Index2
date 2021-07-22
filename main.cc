#include <iostream>
#include <chrono>
#include <index>

#include <index_ui_macros>

global int i;

int main()
{
    var i = Index::INew<int>(100);
    return 0;
}

#include <index_ui_macros_end>