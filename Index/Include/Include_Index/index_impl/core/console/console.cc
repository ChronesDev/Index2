#pragma once

#include "../../std/string/string.cc"
#include <format>
#include <iostream>

#define INDEX_Console_Format(...) std::format(__VA_ARGS__)

#if defined(__clang__)
#undef INDEX_Console_Format
#define INDEX_Console_Format(...) std::string("Not supported yet.")
#elif defined(__GNUC__) || defined(__GNUG__)
#undef INDEX_Console_Format
#define INDEX_Console_Format(...) std::string("Not supported yet.")
#elif defined(_MSC_VER)
#endif

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
        std::cout << INDEX_Console_Format(std::forward<TArg>(arg), std::forward<TArgs>(args)...) << std::endl;
    }
    template <class... TArgs> auto Console::WriteF(TArgs&&... args) -> void { std::cout << INDEX_Console_Format(std::forward<TArgs>(args)...); }
    template <class... TArgs> auto Console::WriteLineF(TArgs&&... args) -> void
    {
        std::cout << INDEX_Console_Format(std::forward<TArgs>(args)...) << std::endl;
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