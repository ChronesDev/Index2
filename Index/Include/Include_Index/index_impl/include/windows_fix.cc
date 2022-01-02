#ifndef INDEX_NO_WINDOWS_H

#if !__has_include(<Windows.h>)
#define INDEX_NO_WINDOWS_H
#endif

#endif

#ifndef INDEX_NO_WINDOWS_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <Windows.h>
#include <Psapi.h>

#ifdef RGB
#undef RGB
#endif

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#endif
