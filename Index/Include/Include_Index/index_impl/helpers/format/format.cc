#pragma once

#include "../compiler/compiler.cc"
#include "../version/version.cc"

// Begin compiler checks
#ifndef INDEX_NoStdFormat

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