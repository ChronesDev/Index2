#pragma once

#include "../../helpers/include.cc"
#include <vector>

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
    template <class T> struct List : public std::vector<T>
    {
    public:
        using std::vector<T>::vector;

        ALIAS_RECLASS_CONSTRUCTOR(List, std::vector<T>)

    public:
        using Iterator = typename std::vector<T>::iterator;

    public:
        constexpr bool Remove(const T& value)
        {
            auto result = std::find(this->begin(), this->end(), value);
            if (result != this->end())
            {
                this->erase(result);
                return false;
            }
            return false;
        }
        constexpr bool RemoveAll(const T& value)
        {
            auto r = std::remove(this->begin(), this->end(), value);
            if (r == this->end()) return false;
            this->erase(r, this->end());
            return true;
        }
        constexpr void SetFirst(T&& value)
        {
            T& first = this->front();
            first = value;
        }
        constexpr void SetLast(T&& value)
        {
            T& first = this->front();
            first = value;
        }
        constexpr bool Contains(const T& value) const { return std::find(this->begin(), this->end(), value) != this->end(); }

    public:
        INDEX_Property(get = target_type) std::type_info& Type;
        INDEX_Property(get = capacity) size_t Capacity;
        INDEX_Property(get = size) size_t Length;
        INDEX_Property(get = front, put = SetFirst) T& First;
        INDEX_Property(get = back, put = SetLast) T& Last;

    public:
        ALIAS_RECLASS_FUNCTION_CONST(T&, At, at)
        ALIAS_RECLASS_FUNCTION(void, Add, push_back)
        ALIAS_RECLASS_FUNCTION(void, Push, push_back)
        ALIAS_RECLASS_FUNCTION(void, Pop, pop_back)
        ALIAS_RECLASS_FUNCTION(void, Clear, clear)
        ALIAS_RECLASS_FUNCTION(void, Swap, swap)
        ALIAS_RECLASS_FUNCTION(void, Assign, assign)
        ALIAS_RECLASS_FUNCTION(Iterator, Erase, erase)
        ALIAS_RECLASS_FUNCTION(void, Reserve, reserve)
        ALIAS_RECLASS_FUNCTION(void, Resize, resize)
    };
}

#undef ALIAS_RECLASS_CONSTRUCTOR
#undef ALIAS_RECLASS_FUNCTION
#undef ALIAS_RECLASS_FUNCTION_CONST