#pragma once

#include <memory>

#define ALIAS_RECLASS_CONSTRUCTOR(this_type, base_type) \
    __forceinline this_type(base_type& other) { static_cast<base_type&>(*this) = other; } \
    __forceinline this_type(base_type&& other) { static_cast<base_type&>(*this) = other; }

#define ALIAS_RECLASS_FUNCTION(this_return_type, this_function, base_function) \
    template<class... TArgs> \
    __forceinline this_return_type this_function(TArgs&&... args) { return this->base_function(std::forward<TArgs>(args)...); }

#define ALIAS_RECLASS_FUNCTION_CONST(this_return_type, this_function, base_function) \
    template<class... TArgs> \
    __forceinline this_return_type this_function(TArgs&&... args) const { return this->base_function(std::forward<TArgs>(args)...); }

namespace Index
{
    template<class T>
    struct IPtr : public std::shared_ptr<T>
    {
    public:
        using std::shared_ptr<T>::shared_ptr;
        ALIAS_RECLASS_CONSTRUCTOR(IPtr, std::shared_ptr<T>)
    public:
        bool GetIsNull() { return this->operator bool(); }
        T& GetValue() { return *this->get(); }
    public:
        __declspec(property(get = GetIsNull)) bool IsNull;
        __declspec(property(get = get)) T* Get;
        __declspec(property(get = get)) T* Ptr;
        __declspec(property(get = GetValue)) T& Value;
    public:
        ALIAS_RECLASS_FUNCTION(void, Swap, swap)
        ALIAS_RECLASS_FUNCTION(void, Reset, reset)
        ALIAS_RECLASS_FUNCTION_CONST(bool, OwnerBefore, owner_before)
    };

    template<class T>
    struct RPtr : public std::weak_ptr<T>
    {
    public:
        using std::weak_ptr<T>::weak_ptr;
        ALIAS_RECLASS_CONSTRUCTOR(RPtr, std::weak_ptr<T>)
    public:
        bool GetIsNull() { return this->operator bool(); }
        T& GetValue() { return *this->get(); }
        IPtr<T> Lock() { return this->lock(); }
    public:
        __declspec(property(get = GetIsNull)) bool IsNull;
        __declspec(property(get = get)) T* Get;
        __declspec(property(get = get)) T* Ptr;
        __declspec(property(get = GetValue)) T& Value;
        __declspec(property(get = expired)) T& Expired;
    public:
        ALIAS_RECLASS_FUNCTION(void, Swap, swap)
        ALIAS_RECLASS_FUNCTION(void, Reset, reset)
        ALIAS_RECLASS_FUNCTION_CONST(bool, OwnerBefore, owner_before)
        ALIAS_RECLASS_FUNCTION_CONST(long, UseCount, use_count)
    };

    template<class T>
    struct UPtr : public std::unique_ptr<T>
    {
    public:
        using std::unique_ptr<T>::unique_ptr;
        template<class name>
        __forceinline UPtr(std::unique_ptr<T>& other) { static_cast<std::unique_ptr<T>&>(*this) = other; }
        __forceinline UPtr(std::unique_ptr<T>&& other) : std::unique_ptr<T>(std::forward<std::unique_ptr<T>>(other)) {
        }
    public:
        bool GetIsNull() { return this->operator bool(); }
        T& GetValue() { return *this->get(); }
    public:
        __declspec(property(get = GetIsNull)) bool IsNull;
        __declspec(property(get = get)) T* Get;
        __declspec(property(get = get)) T* Ptr;
        __declspec(property(get = GetValue)) T& Value;
    public:
        ALIAS_RECLASS_FUNCTION(void, Swap, swap)
        ALIAS_RECLASS_FUNCTION(void, Reset, reset)
        ALIAS_RECLASS_FUNCTION(void, Release, release)
    };

    template<class T, class... TArgs>
    __forceinline IPtr<T> INew(TArgs&&... args) { return std::make_shared<T>(std::forward<TArgs>(args)...); }

    template<class T, class... TArgs>
    __forceinline UPtr<T> UNew(TArgs&&... args) { return std::make_unique<T>(std::forward<TArgs>(args)...); }
}

#undef ALIAS_RECLASS_CONSTRUCTOR
#undef ALIAS_RECLASS_FUNCTION
#undef ALIAS_RECLASS_FUNCTION_CONST