#pragma once

#include "../compiler/compiler.cc"

// Check for a supported compiler
#ifdef INDEX_SupportedCompiler

// Compiler is supported
#define INDEX_Property(...) __declspec(property(__VA_ARGS__))

// Compiler is not supported
#else

/**
 * The C++ Properties extension is not available. Make sure to use a supported compiler.
 */
#error index: The C++ Properties extension is not available

#endif