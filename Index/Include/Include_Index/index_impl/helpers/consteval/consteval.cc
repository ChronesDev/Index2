#pragma once

#if __cplusplus > 202002L || defined(_MSC_VER)
#define INDEX_Consteval consteval
#else
#define INDEX_Consteval constexpr
#endif