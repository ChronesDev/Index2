#pragma once

#include "../../helpers/include.cc"
#include <tuple>

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
    template <class T1, class T2> struct Pair : public std::pair<T1, T2>
    {
    private:
        using BaseType = std::pair<T1, T2>;

    public:
        using std::pair<T1, T2>::pair;

        ALIAS_RECLASS_CONSTRUCTOR(Pair, BaseType)

    public:
        template <class T> T& Get() const { return std::get<T>(*this); }
        template <size_t TIndex> std::tuple_element_t<TIndex, std::pair<T1, T2>>& Get()
        {
            return std::get<TIndex, T1, T2>(*this);
        }

    public:
        INDEX_Property(get = first) T1& First;
        INDEX_Property(get = second) T2& Second;

    public:
        ALIAS_RECLASS_FUNCTION(void, Swap, swap)
    };
}

#undef ALIAS_RECLASS_CONSTRUCTOR
#undef ALIAS_RECLASS_FUNCTION
#undef ALIAS_RECLASS_FUNCTION_CONST