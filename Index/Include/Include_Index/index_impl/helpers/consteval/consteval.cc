#pragma once

#include "../version/version.cc"

#ifdef INDEX_Cpp20
#define INDEX_Consteval consteval
#else
#define INDEX_Consteval constexpr
#endif