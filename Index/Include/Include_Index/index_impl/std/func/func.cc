#pragma once

#include "../../helpers/include.cc"
#include <functional>

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
    template <class T> struct Func : public std::function<T>
    {
    public:
        using std::function<T>::function;

        ALIAS_RECLASS_CONSTRUCTOR(Func, std::function<T>);

    public:
        INDEX_Property(get = target_type) type_info& Type;

    public:
        ALIAS_RECLASS_FUNCTION(void, Swap, swap);
    };
}

namespace Index
{
    template <class T, class... TArgs> Func<T> Bind(T&& f, TArgs&&... args)
    {
        return std::bind<T>(std::forward<T>(f), std::forward<TArgs>(args)...);
    }
}

#undef ALIAS_RECLASS_CONSTRUCTOR
#undef ALIAS_RECLASS_FUNCTION
#undef ALIAS_RECLASS_FUNCTION_CONST