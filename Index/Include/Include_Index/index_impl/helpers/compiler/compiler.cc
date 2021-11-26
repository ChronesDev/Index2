#pragma once

#if defined(_MSC_VER)
#define INDEX_IsMSVC
#define INDEX_CompilerName "MSVC"

#elif defined(__clang__)
#define INDEX_IsClang
#define INDEX_CompilerName "Clang"

#elif defined(__GNUC__) || defined(__GNUG__)
#define INDEX_IsGNU
#define INDEX_CompilerName "GNU"

#else
#define INDEX_IsUnknown
#define INDEX_CompilerName "Unkown"
#endif