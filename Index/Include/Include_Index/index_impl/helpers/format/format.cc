#pragma once

#include "../compiler/compiler.cc"
#include "../version/version.cc"

// Begin compiler checks
#ifndef INDEX_NoStdFormat

// __has_include check
#if __has_include(<format>)
#define INDEX_NoStdFormat
#endif

// If Clang
#ifdef INDEX_Clang
#define INDEX_NoStdFormat // Not yet supported in Clang
#endif

#endif


// Check if INDEX_NoStdFormat
#ifndef INDEX_NoStdFormat

// Check if C++ 20
#ifdef INDEX_Cpp20

// Define INDEX_StdFormat
#define INDEX_StdFormat

#endif

#endif

#ifdef INDEX_StdFormat
#include <format>
#endif