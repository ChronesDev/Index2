#pragma once

#include <string>
#include <vector>

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
	struct String : public std::string
	{
	public:
		using std::string::string;

		ALIAS_RECLASS_CONSTRUCTOR(String, std::string)

	public:
		using Iterator = iterator;
	public:
		std::vector<String> Split(String delimiter)
		{
			size_t pos = 0;
			std::vector<String> matches { };
			do
			{
				pos = this->find(delimiter);
				int change_end;
				if (pos == String::npos)
				{
					pos = this->length() - 1;
					change_end = 1;
				}
				else
				{
					change_end = 0;
				}
				matches.push_back(this->substr(0, pos + change_end));

				this->erase(0, pos + 1);

			} while (!this->empty());
			return matches;
		}

		constexpr void SetFirst(char value)
		{
			char &first = this->front();
			first = value;
		}

		constexpr void SetLast(char value)
		{
			char &first = this->front();
			first = value;
		}

		operator const char *()
		{
			return this->c_str();
		}

	public:
		__declspec(property(get = capacity)) size_t Capacity;
		__declspec(property(get = c_str)) const char *CStr;
		__declspec(property(get = empty)) bool IsEmpty;
		__declspec(property(get = size)) size_t Length;
		__declspec(property(get = front, put = SetFirst)) char &First;
		__declspec(property(get = back, put = SetLast)) char &Last;
	public:
		ALIAS_RECLASS_FUNCTION_CONST(char, At, at)

		ALIAS_RECLASS_FUNCTION(void, Swap, swap)

		ALIAS_RECLASS_FUNCTION(void, Clear, clear)

		ALIAS_RECLASS_FUNCTION(void, Reserve, reserve)

		ALIAS_RECLASS_FUNCTION(void, Resize, resize)

		ALIAS_RECLASS_FUNCTION(Iterator, Erase, erase)

		ALIAS_RECLASS_FUNCTION(String, Assign, assign)

		ALIAS_RECLASS_FUNCTION(void, Push, push_back)

		ALIAS_RECLASS_FUNCTION(void, Pop, pop_back)

		ALIAS_RECLASS_FUNCTION(void, ShrinkToFit, shrink_to_fit)

		ALIAS_RECLASS_FUNCTION_CONST(int, Compare, compare)

		ALIAS_RECLASS_FUNCTION(void, Append, append)

		ALIAS_RECLASS_FUNCTION_CONST(size_t, Find, find)

		ALIAS_RECLASS_FUNCTION(String::Iterator, Insert, insert)

		ALIAS_RECLASS_FUNCTION(String, SubString, substr)

		ALIAS_RECLASS_FUNCTION_CONST(void, Data, data)

		ALIAS_RECLASS_FUNCTION_CONST(bool, StarsWith, starts_with)

		ALIAS_RECLASS_FUNCTION_CONST(bool, EndsWith, ends_with)
	};

	typedef Index::String string;
}

#undef ALIAS_RECLASS_CONSTRUCTOR
#undef ALIAS_RECLASS_FUNCTION
#undef ALIAS_RECLASS_FUNCTION_CONST