#pragma once

#include "../../helpers/include.cc"
#include "../console/console.cc"

namespace Index
{
    class DebugI
    {
        DebugI() = default;

    public:
        template <class TArg, class... TArgs> inline auto Log(TArg&& arg, TArgs&&... args) const -> void;
        template <class... TArgs> inline auto Write(TArgs&&... args) const -> void;
        template <class... TArgs> inline auto WriteLine(TArgs&&... args) const -> void;

        template <class TArg, class... TArgs> inline auto LogF(TArg&& arg, TArgs&&... args) const -> void;
        template <class... TArgs> inline auto WriteF(TArgs&&... args) const -> void;
        template <class... TArgs> inline auto WriteLineF(TArgs&&... args) const -> void;

        inline auto ReadKey() const -> int;
        inline auto ReadLine() const -> string;

    public:
        inline static auto New() noexcept -> DebugI;
    };

    inline DebugI Debug = DebugI::New();

#pragma region Implementation

    template <class TArg, class... TArgs> auto DebugI::Log(TArg&& arg, TArgs&&... args) const -> void
    {
#ifdef INDEX_DEBUG
        std::cout << arg;
        (std::cout << ... << args);
        std::cout << std::endl;
#endif
    }
    template <class... TArgs> auto DebugI::Write(TArgs&&... args) const -> void
    {
#ifdef INDEX_DEBUG
        (std::cout << ... << args);
#endif
    }
    template <class... TArgs> auto DebugI::WriteLine(TArgs&&... args) const -> void
    {
#ifdef INDEX_DEBUG
        (std::cout << ... << args);
        std::cout << std::endl;
#endif
    }

    template <class TArg, class... TArgs> auto DebugI::LogF(TArg&& arg, TArgs&&... args) const -> void
    {
#ifdef INDEX_DEBUG
        std::cout << INDEX_Console_Format(std::forward<TArg>(arg), std::forward<TArgs>(args)...) << std::endl;
#endif
    }
    template <class... TArgs> auto DebugI::WriteF(TArgs&&... args) const -> void
    {
#ifdef INDEX_DEBUG
        std::cout << INDEX_Console_Format(std::forward<TArgs>(args)...);
#endif
    }
    template <class... TArgs> auto DebugI::WriteLineF(TArgs&&... args) const -> void
    {
#ifdef INDEX_DEBUG
        std::cout << INDEX_Console_Format(std::forward<TArgs>(args)...) << std::endl;
#endif
    }

    auto DebugI::ReadKey() const -> int
    {
#ifdef INDEX_DEBUG
        return std::cin.get();
#endif
    }
    auto DebugI::ReadLine() const -> string
    {
#ifdef INDEX_DEBUG
        string ret;
        std::getline(std::cin, ret);
        return ret;
#endif
    }

#pragma endregion

#pragma region StaticImplementation

    auto DebugI::New() noexcept -> DebugI { return {}; }

#pragma endregion
}