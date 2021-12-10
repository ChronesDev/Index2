#pragma once

#include "../../std/string/string.cc"
#include <iostream>

#define INDEX_Console_Format(...) std::format(__VA_ARGS__)

#ifndef INDEX_StdFormat
#undef INDEX_Console_Format
#define INDEX_Console_Format(...) "[Index: std::format not supported.]"
#endif

namespace Index
{
    class ConsoleI
    {
        ConsoleI() = default;

    public:
        template <class TArg, class... TArgs> inline auto Log(TArg&& arg, TArgs&&... args) const -> void;
        template <class... TArgs> inline auto Write(TArgs&&... args) const -> void;
        template <class... TArgs> inline auto WriteLine(TArgs&&... args) const -> void;

        template <class TArg, class... TArgs> inline auto LogF(TArg&& arg, TArgs&&... args) const -> void;
        template <class... TArgs> inline auto WriteF(TArgs&&... args) const -> void;
        template <class... TArgs> inline auto WriteLineF(TArgs&&... args) const -> void;

        [[nodiscard]] inline auto ReadKey() const -> int;
        [[nodiscard]] inline auto ReadLine() const -> string;

    public:
        inline static auto New() noexcept -> ConsoleI;
    };

    inline ConsoleI Console = ConsoleI::New();

#pragma region Implementation

    template <class TArg, class... TArgs> auto ConsoleI::Log(TArg&& arg, TArgs&&... args) const -> void
    {
        std::cout << arg;
        (std::cout << ... << args);
        std::cout << std::endl;
    }
    template <class... TArgs> auto ConsoleI::Write(TArgs&&... args) const -> void { (std::cout << ... << args); }
    template <class... TArgs> auto ConsoleI::WriteLine(TArgs&&... args) const -> void
    {
        (std::cout << ... << args);
        std::cout << std::endl;
    }

    template <class TArg, class... TArgs> auto ConsoleI::LogF(TArg&& arg, TArgs&&... args) const -> void
    {
        std::cout << INDEX_Console_Format(std::forward<TArg>(arg), std::forward<TArgs>(args)...) << std::endl;
    }
    template <class... TArgs> auto ConsoleI::WriteF(TArgs&&... args) const -> void
    {
        std::cout << INDEX_Console_Format(std::forward<TArgs>(args)...);
    }
    template <class... TArgs> auto ConsoleI::WriteLineF(TArgs&&... args) const -> void
    {
        std::cout << INDEX_Console_Format(std::forward<TArgs>(args)...) << std::endl;
    }

    auto ConsoleI::ReadKey() const -> int { return std::cin.get(); }
    auto ConsoleI::ReadLine() const -> string
    {
        string ret;
        std::getline(std::cin, ret);
        return ret;
    }

#pragma endregion

#pragma region StaticImplementation

    auto ConsoleI::New() noexcept -> ConsoleI { return {}; }

#pragma endregion
}