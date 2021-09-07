/*
 * Windows.h FIX:
 *  RGB
 */

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "Windows.h"

#ifdef RGB
#undef RGB
#endif
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif
