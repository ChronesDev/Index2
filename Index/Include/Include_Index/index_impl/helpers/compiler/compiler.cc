#pragma once

// Determines whether the current compiler is supported
#define INDEX_SupportedCompiler

// Check for Clang compiler
#if defined(__clang__)
#define INDEX_Clang
#define INDEX_CompilerName "Clang"

// Check for GNU compiler
#elif defined(__GNUC__) || defined(__GNUG__)
#define INDEX_GNU
#define INDEX_CompilerName "GNU"

// Check for MSVC compiler
#elif defined(_MSC_VER)
#define INDEX_MSVC
#define INDEX_CompilerName "MSVC"

// Custom Supported Compiler
#elifdef INDEX_CustomCompiler
#define INDEX_CompilerName "Custom"

// Not Supported
#else
#undef INDEX_SupportedCompiler
#define INDEX_UnsupportedCompiler
#define INDEX_CompilerName "Unknown"

/**
 * The current compiler you are currently using is not supported.
 * Make sure that the current compiler has the needed feature support.
 * If it has then define INDEX_CustomCompiler globally to suppress this error
 */
#error index: Unsupported compiler. To disable this error, define INDEX_CustomCompiler globally

#endif