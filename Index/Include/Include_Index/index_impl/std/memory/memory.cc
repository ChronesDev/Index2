#pragma once

#include "../../helpers/include.cc"
#include <memory>

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
    template <class T> [[nodiscard]] constexpr std::remove_reference_t<T&&> Move(T&& _Arg) noexcept
    { // forward _Arg as movable
        return static_cast<std::remove_reference_t<T>&&>(_Arg);
    }

    template <class T> [[nodiscard]] constexpr T&& Forward(std::remove_reference_t<T>& e) noexcept
    { // forward an lvalue as either an lvalue or an rvalue
        return static_cast<T&&>(e);
    }

    template <class T> [[nodiscard]] constexpr T&& Forward(std::remove_reference_t<T>&& e) noexcept
    { // forward an rvalue as an rvalue
        static_assert(!std::is_lvalue_reference_v<T>, "bad forward call");
        return static_cast<T&&>(e);
    }

    template <typename T> [[nodiscard]] constexpr T DefaultOf() noexcept { return T {}; }
}

namespace Index
{
    template <class T> struct IPtr : public std::shared_ptr<T>
    {
    public:
        using std::shared_ptr<T>::shared_ptr;

        ALIAS_RECLASS_CONSTRUCTOR(IPtr, std::shared_ptr<T>)

    public:
        template <class TTo> IPtr<TTo> As() const { return std::static_pointer_cast<TTo>(*this); }
        template <class TTo> IPtr<TTo> StaticAs() const { return std::static_pointer_cast<TTo>(*this); }
        template <class TTo> IPtr<TTo> DynamicAs() const { return std::dynamic_pointer_cast<TTo>(*this); }
        template <class TTo> IPtr<TTo> ConstAs() const { return std::const_pointer_cast<TTo>(*this); }
        template <class TTo> IPtr<TTo> ReinterpretAs() const { return std::reinterpret_pointer_cast<TTo>(*this); }

        bool GetIsNull() const { return !(this->operator bool()); }

        T& GetValue() const { return *this->get(); }

    public:
        static __forceinline IPtr<T> Null() { return {}; }

    public:
        INDEX_Property(get = GetIsNull) bool IsNull;
        INDEX_Property(get = get) T* Get;
        INDEX_Property(get = get) T* Ptr;
        INDEX_Property(get = GetValue) T& Value;

    public:
        ALIAS_RECLASS_FUNCTION(void, Swap, swap)
        ALIAS_RECLASS_FUNCTION(void, Reset, reset)
        ALIAS_RECLASS_FUNCTION_CONST(bool, OwnerBefore, owner_before)
    };

    template <class T> struct WPtr : public std::weak_ptr<T>
    {
    public:
        using std::weak_ptr<T>::weak_ptr;

        ALIAS_RECLASS_CONSTRUCTOR(WPtr, std::weak_ptr<T>)

    public:
        template <class TTo> WPtr<TTo> As() const { return std::static_pointer_cast<TTo>(this->lock()); }
        template <class TTo> WPtr<TTo> StaticAs() const { return std::static_pointer_cast<TTo>(this->lock()); }
        template <class TTo> WPtr<TTo> DynamicAs() const { return std::dynamic_pointer_cast<TTo>(this->lock()); }
        template <class TTo> WPtr<TTo> ConstAs() const { return std::const_pointer_cast<TTo>(this->lock()); }
        template <class TTo> WPtr<TTo> ReinterpretAs() const { return std::reinterpret_pointer_cast<TTo>(this->lock()); }

        bool GetIsNull() const { return this->expired(); }
        IPtr<T> GetLock() const { return this->lock(); }

        template <class TTo> IPtr<TTo> LockAs() const { return std::static_pointer_cast<TTo>(this->lock()); }
        template <class TTo> IPtr<TTo> LockStaticAs() const { return std::static_pointer_cast<TTo>(this->lock()); }
        template <class TTo> IPtr<TTo> LockDynamicAs() const { return std::dynamic_pointer_cast<TTo>(this->lock()); }
        template <class TTo> IPtr<TTo> LockConstAs() const { return std::const_pointer_cast<TTo>(this->lock()); }
        template <class TTo> IPtr<TTo> LockReinterpretAs() const { return std::reinterpret_pointer_cast<TTo>(this->lock()); }

    public:
        bool operator==(const WPtr& other)
        {
            auto l1 = this->Lock;
            auto l2 = other.Lock;
            return l1 == l2;
        }

    public:
        static __forceinline IPtr<T> Null() { return {}; }

        INDEX_Property(get = GetIsNull) bool IsNull;
        INDEX_Property(get = expired) bool Expired;
        INDEX_Property(get = GetLock) IPtr<T> Lock;

    public:
        ALIAS_RECLASS_FUNCTION(void, Swap, swap)
        ALIAS_RECLASS_FUNCTION(void, Reset, reset)
        ALIAS_RECLASS_FUNCTION_CONST(bool, OwnerBefore, owner_before)
        ALIAS_RECLASS_FUNCTION_CONST(long, UseCount, use_count)
    };

    template <class T> struct UPtr : public std::unique_ptr<T>
    {
    public:
        using std::unique_ptr<T>::unique_ptr;

        template <class name> __forceinline UPtr(std::unique_ptr<T>& other)
        {
            static_cast<std::unique_ptr<T>&>(*this) = other;
        }

        __forceinline UPtr(std::unique_ptr<T>&& other)
            : std::unique_ptr<T>(std::forward<std::unique_ptr<T>>(other))
        {
        }

    public:
        template <class TTo> IPtr<TTo> As() const { return std::static_pointer_cast<TTo>(*this); }
        template <class TTo> IPtr<TTo> StaticAs() const { return std::static_pointer_cast<TTo>(*this); }
        template <class TTo> IPtr<TTo> DynamicAs() const { return std::dynamic_pointer_cast<TTo>(*this); }
        template <class TTo> IPtr<TTo> ConstAs() const { return std::const_pointer_cast<TTo>(*this); }
        template <class TTo> IPtr<TTo> ReinterpretAs() const { return std::reinterpret_pointer_cast<TTo>(*this); }

        bool GetIsNull() const { return !(this->operator bool()); }
        T& GetValue() const { return *this->get(); }

    public:
        INDEX_Property(get = GetIsNull) bool IsNull;
        INDEX_Property(get = get) T* Get;
        INDEX_Property(get = get) T* Ptr;
        INDEX_Property(get = GetValue) T& Value;

    public:
        ALIAS_RECLASS_FUNCTION(void, Swap, swap)
        ALIAS_RECLASS_FUNCTION(void, Reset, reset)
        ALIAS_RECLASS_FUNCTION(void, Release, release)
    };

    template <class T> struct IObj : public std::enable_shared_from_this<T>
    {
        [[nodiscard]] __forceinline IPtr<T> ISelf() { return this->shared_from_this(); }
        [[nodiscard]] __forceinline IPtr<T> ISelf() const { return this->shared_from_this(); }
        [[nodiscard]] __forceinline WPtr<T> WSelf() { return this->weak_from_this(); }
        [[nodiscard]] __forceinline WPtr<T> WSelf() const { return this->weak_from_this(); }
    };

    template <class T, class... TArgs> __forceinline IPtr<T> INew(TArgs&&... args)
    {
        return std::make_shared<T>(std::forward<TArgs>(args)...);
    }

    template <class T, class... TArgs> __forceinline UPtr<T> UNew(TArgs&&... args)
    {
        return std::make_unique<T>(std::forward<TArgs>(args)...);
    }
}

#undef ALIAS_RECLASS_CONSTRUCTOR
#undef ALIAS_RECLASS_FUNCTION
#undef ALIAS_RECLASS_FUNCTION_CONST