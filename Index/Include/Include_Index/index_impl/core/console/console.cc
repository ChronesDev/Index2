#pragma once

#include "../../std/string/string.cc"
#include <format>
#include <iostream>

namespace Index
{
    class Console final
    {
        Console() = default;

    public:
        template <class TArg, class... TArgs> inline static auto Log(TArg&& arg, TArgs&&... args) -> void;
        template <class... TArgs> inline static auto Write(TArgs&&... args) -> void;
        template <class... TArgs> inline static auto WriteLine(TArgs&&... args) -> void;

        template <class TArg, class... TArgs> inline static auto LogF(TArg&& arg, TArgs&&... args) -> void;
        template <class... TArgs> inline static auto WriteF(TArgs&&... args) -> void;
        template <class... TArgs> inline static auto WriteLineF(TArgs&&... args) -> void;

        inline static auto ReadKey() -> int;
        inline static auto ReadLine() -> string;
    };

    template <class TArg, class... TArgs> auto Console::Log(TArg&& arg, TArgs&&... args) -> void
    {
        std::cout << arg;
        (std::cout << ... << args);
        std::cout << std::endl;
    }
    template <class... TArgs> auto Console::Write(TArgs&&... args) -> void { (std::cout << ... << args); }
    template <class... TArgs> auto Console::WriteLine(TArgs&&... args) -> void
    {
        (std::cout << ... << args);
        std::cout << std::endl;
    }

    template <class TArg, class... TArgs> auto Console::LogF(TArg&& arg, TArgs&&... args) -> void
    {
        std::cout << std::format(std::forward<TArg>(arg), std::forward<TArgs>(args)...) << std::endl;
    }
    template <class... TArgs> auto Console::WriteF(TArgs&&... args) -> void { std::cout << std::format(std::forward<TArgs>(args)...); }
    template <class... TArgs> auto Console::WriteLineF(TArgs&&... args) -> void
    {
        std::cout << std::format(std::forward<TArgs>(args)...) << std::endl;
    }

    auto Console::ReadKey() -> int
    {
        return std::cin.get();
    }
    auto Console::ReadLine() -> string
    {
        string ret;
        std::getline(std::cin, ret);
        return ret;
    }
}