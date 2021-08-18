#pragma once

#include <variant>

#define ALIAS_RECLASS_CONSTRUCTOR(this_type, base_type) \
__forceinline this_type(base_type& other) { static_cast<base_type&>(*this) = other; } \
__forceinline this_type(base_type&& other) { static_cast<base_type&>(*this) = other; }

#define ALIAS_RECLASS_FUNCTION(this_return_type, this_function, base_function) \
template<class... TArgs> \
__forceinline this_return_type this_function(TArgs&&... args) { return this->base_function(std::forward<TArgs>(args)...); }

#define ALIAS_RECLASS_FUNCTION_CONST(this_return_type, this_function, base_function) \
template<class... TArgs> \
__forceinline this_return_type this_function(TArgs&&... args) const { return this->base_function(std::forward<TArgs>(args)...); }

// TODO: Finish Variant class
namespace Index
{
    template<class... TTypes>
struct Variant : public std::variant<TTypes...>
    {
    public:
        using std::variant<TTypes...>::variant;
        ALIAS_RECLASS_CONSTRUCTOR(Variant, std::variant<TTypes...>)
    public:
    public:
        //__declspec(property(get = capacity)) size_t Capacity;
    public:
        ALIAS_RECLASS_FUNCTION_CONST(void, Swap, swap)
    };
}


#undef ALIAS_RECLASS_CONSTRUCTOR
#undef ALIAS_RECLASS_FUNCTION
#undef ALIAS_RECLASS_FUNCTION_CONST