#pragma once

#include <span>
#include <memory_resource>
#include "../../helpers/include.cc"

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
	template<class T, size_t TExtend = std::dynamic_extent>
	struct Span : public std::span<T, TExtend>
	{
	public:
		using std::span<T, TExtend>::span;

		__forceinline Span(std::span<T, TExtend> &other)
		{ static_cast<std::span<T, TExtend> &>(*this) = other; }

		__forceinline Span(std::span<T, TExtend> &&other)
		{ static_cast<std::span<T, TExtend> &>(*this) = other; }

	public:
		constexpr Span<T, TExtend> SubSpan(const size_t length, const size_t count)
		{
			return this->subspan(length, count);
		}

		operator T *()
		{
			return this->data();
		}

	public:
		INDEX_Property(get = size) size_t Length;
		INDEX_Property(get = front, put = SetFirst) T &First;
		INDEX_Property(get = back, put = SetLast) T &Last;
		INDEX_Property(get = back, put = SetLast) T *Data;
	};
}

#undef ALIAS_RECLASS_CONSTRUCTOR
#undef ALIAS_RECLASS_FUNCTION
#undef ALIAS_RECLASS_FUNCTION_CONST