#pragma once

// Check for Clang, MSVC or GCC
#if defined(__clang__) || defined(_MSC_VER) || defined(__GNUC__) || defined(__GNUG__)

#define INDEX_Property(...) \
__declspec(property(__VA_ARGS__))

#else

#error "It looks like you are using an unsupported compiler"

#endif