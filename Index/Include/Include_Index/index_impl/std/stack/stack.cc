#pragma once

#include "../../helpers/include.cc"
#include <stack>

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
    template <class T> struct Stack : public std::stack<T>
    {
    public:
        using std::stack<T>::stack;

        ALIAS_RECLASS_CONSTRUCTOR(Stack, std::stack<T>)

    public:
        Stack& operator+=(T& other)
        {
            this->push(other);
            return *this;
        }

        Stack& operator+=(T&& other)
        {
            this->push(other);
            return *this;
        }

        Stack& operator-()
        {
            this->pop();
            return *this;
        }

        T& operator+() { return this->top(); }

    public:
        INDEX_Property(get = target_type) std::type_info& Type;
        INDEX_Property(get = capacity) size_t Capacity;
        INDEX_Property(get = size) size_t Length;
        INDEX_Property(get = top) T& Top;

    public:
        ALIAS_RECLASS_FUNCTION_CONST(T&, At, at)
        ALIAS_RECLASS_FUNCTION(void, Push, push)
        ALIAS_RECLASS_FUNCTION(void, Pop, pop)
        ALIAS_RECLASS_FUNCTION(void, Swap, swap)
    };
}

#undef ALIAS_RECLASS_CONSTRUCTOR
#undef ALIAS_RECLASS_FUNCTION
#undef ALIAS_RECLASS_FUNCTION_CONST