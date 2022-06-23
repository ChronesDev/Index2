> :warning: This project has been deprecated by [**chr**](https://github.com/ChronesIO/chr)

# Index2
[![](https://tokei.rs/b1/github/ChronesDev/Index2?category=files)](https://github.com/ChronesDev/Index2)
[![](https://tokei.rs/b1/github/ChronesDev/Index2?category=code)](https://github.com/ChronesDev/Index2)

**Index**, an adaptive UI Engine for any renderer.

> **What is Index?** \
> *Index is a UI layout engine which can be adopted in any renderer. 
> What Index does is calculating the alignment and position of each UIElement.
> Also it supports hit testing.

> **Quickdemo**
> ```c++
> #include <index>
> #include <index_ui>
> 
> #include <index_macros>
> #include <index_ui_macros>
> 
> int main()
> {
>     using namespace Index;
>     using namespace Index::UI;
> 
>     sub ContainerMapper mapper;
>     sub Container mapn
>     {
>         set Name = "MyElementName";
> 
>         sub VStack mapn
>         {
>             set MinWidth = 30;
> 
>             sub Container mapn 
>             {
>                 set Name = "My Container 1";
>                 set MinSize = { 10, 20 };
>             };
> 
>             sub Container mapn { set Name = "My Container 2"; };
>         };
>     };
> 
>     // Work in progress
>     Index::UI::DebugHelpers::PrintTree(mapper.Make());
> }
> 
> #include <index_macros_end>
> #include <index_ui_macros_end>
> ```
> **Output**
> ```
> (Container) "MyElementName"
> |-- (VStack)
>     |-- (Container) "My Container 1"
>     |-- (Container) "My Container 2"
> ```
