#pragma once

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
        bool IsIdentical(const Func<T>& other) const
        {
            return *reinterpret_cast<void**>((std::function<T>*)this)
                == *reinterpret_cast<void**>((std::function<T>*)&other);
        }

    public:
        INDEX_Property(get = target_type) std::type_info& Type;

    public:
        ALIAS_RECLASS_FUNCTION(void, Swap, swap);
    };

    template <class... T> using Action = Func<void(T...)>;
}

namespace Index
{
    template <class T, class... TArgs> constexpr decltype(std::bind<T, TArgs...>) Bind(T&& f, TArgs&&... args)
    {
        return std::bind(std::forward<T>(f), std::forward<TArgs>(args)...);
    }

    template <class TFunc, class T, class... TArgs> constexpr Func<TFunc> BindFunc(T&& f, TArgs&&... args)
    {
        Func<TFunc> ret = std::bind(std::forward<T>(f), std::forward<TArgs>(args)...);
        return ret;
    }
}

#undef ALIAS_RECLASS_CONSTRUCTOR
#undef ALIAS_RECLASS_FUNCTION
#undef ALIAS_RECLASS_FUNCTION_CONST