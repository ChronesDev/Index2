#pragma once

#include <vector>

#define ALIAS_RECLASS_CONSTRUCTOR(this_type, base_type) \
    __forceinline this_type(base_type& other) { static_cast<base_type&>(*this) = other; } \
    __forceinline this_type(base_type&& other) { static_cast<base_type&>(*this) = other; }

#define ALIAS_RECLASS_FUNCTION(this_return_type, this_function, base_function) \
    template<class... TArgs> \
    __forceinline this_return_type this_function(TArgs&&... args) { return this->base_function(std::forward<TArgs>(args)...); }

namespace Index
{
    template<class T>
    struct List : public std::vector<T>
    {
    public:
        using std::vector<T>::vector;
        ALIAS_RECLASS_CONSTRUCTOR(List, std::vector<T>)
    public:
        constexpr void Remove(T&& value) {
            auto result = std::find(this->begin(), this->end(), value);
            if (result != this->end())
                this->erase(result);
        }
        constexpr void RemoveAll(T&& value) {
            this->erase(std::remove(this->begin(), this->end(), value), this->end());
        }
        constexpr void SetFirst(T&& value) {
            T& first = this->front();
            first = value;
        }
        constexpr void SetLast(T&& value) {
            T& first = this->front();
            first = value;
        }
    public:
        __declspec(property(get = target_type)) type_info& Type;
        __declspec(property(get = capacity)) size_t Capacity;
        __declspec(property(get = size)) size_t Length;
        __declspec(property(get = front, put = SetFirst)) T& First;
        __declspec(property(get = back, put = SetLast)) T& Last;
    public:
        ALIAS_RECLASS_FUNCTION(void, At, at)
        ALIAS_RECLASS_FUNCTION(void, Add, push_back)
        ALIAS_RECLASS_FUNCTION(void, Push, push_back)
        ALIAS_RECLASS_FUNCTION(void, Pop, pop_back)
        ALIAS_RECLASS_FUNCTION(void, Clear, clear)
        ALIAS_RECLASS_FUNCTION(void, Swap, swap)
        ALIAS_RECLASS_FUNCTION(void, Assign, assign)
        ALIAS_RECLASS_FUNCTION(void, Erase, erase)
        ALIAS_RECLASS_FUNCTION(void, Reserve, reserve)
        ALIAS_RECLASS_FUNCTION(void, Resize, resize)
    };
}

#undef ALIAS_RECLASS_CONSTRUCTOR
#undef ALIAS_RECLASS_FUNCTION