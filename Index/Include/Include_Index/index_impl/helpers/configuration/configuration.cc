#pragma once

// Check if manually defined
#ifdef INDEX_DEBUG

// Custom Configuration
#define INDEX_UsesCustomConfigurationMode

// Cannot be DEBUG while also being RELEASE
#ifdef INDEX_RELEASE

#error index: Wrong manual configuration. INDEX_DEBUG and INDEX_RELEASE cannot appear at the same time.

#endif

// Check if manually defined
#elifdef INDEX_RELEASE

// Custom Configuration
#define INDEX_UsesCustomConfigurationMode

// Cannot be DEBUG while also being RELEASE
#ifdef INDEX_DEBUG

#error index: Wrong manual configuration. INDEX_DEBUG and INDEX_RELEASE cannot appear at the same time.

#endif

#endif

// Does not define INDEX_DEBUG or INDEX_RELEASE manually
#ifndef INDEX_UsesCustomConfigurationMode

// Debug
#ifdef _DEBUG

// INDEX_DEBUG
#define INDEX_DEBUG

#elifndef NDEBUG

// INDEX_DEBUG
#define INDEX_DEBUG

#else

// INDEX_RELEASE
#define INDEX_RELEASE

#endif

#endif