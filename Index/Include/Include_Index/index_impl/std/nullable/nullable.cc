#pragma once

#include "../../helpers/include.cc"
#include <optional>

#define ALIAS_RECLASS_CONSTRUCTOR(this_type, base_type)                                                               \
    __forceinline this_type(base_type& other) { static_cast<base_type&>(*this) = other; }                             \
    __forceinline this_type(base_type&& other) { static_cast<base_type&>(*this) = other; }

#define ALIAS_RECLASS_FUNCTION(this_return_type, this_function, base_function)                                        \
    template <class... TArgs> __forceinline this_return_type this_function(TArgs&&... args)                           \
    {                                                                                                                 \
        return this->base_function(std::forward<TArgs>(args)...);                                                     \
    }

#define ALIAS_RECLASS_FUNCTION_CONST(this_return_type, this_function, base_function)                                  \
    template <class... TArgs> __forceinline this_return_type this_function(TArgs&&... args) const                     \
    {                                                                                                                 \
        return this->base_function(std::forward<TArgs>(args)...);                                                     \
    }

namespace Index
{
    struct NullT : public std::nullopt_t
    {
        using std::nullopt_t::nullopt_t;

        constexpr explicit NullT()
            : std::nullopt_t({})
        {
        }
    };

    inline constexpr NullT Null;

    template <class T> struct Nullable : public std::optional<T>
    {
    public:
        using std::optional<T>::optional;

        ALIAS_RECLASS_CONSTRUCTOR(Nullable, std::optional<T>)

    public:
        INDEX_Property(get = value) T& Value;
        INDEX_Property(get = has_value) T& HasValue;

    public:
        ALIAS_RECLASS_FUNCTION(void, Swap, swap)

        ALIAS_RECLASS_FUNCTION(void, Reset, reset)

        ALIAS_RECLASS_FUNCTION_CONST(std::remove_cv_t<T>, ValueOr, value_or)

        ALIAS_RECLASS_FUNCTION(T&, Emplace, emplace)
    };
}

#undef ALIAS_RECLASS_CONSTRUCTOR
#undef ALIAS_RECLASS_FUNCTION
#undef ALIAS_RECLASS_FUNCTION_CONST