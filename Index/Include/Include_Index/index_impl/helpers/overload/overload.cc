#pragma once

/**
 * Macro Overloading: Allows the overloading of macros.
 *
 * Usage:
 *  #define MY_MACRO(...) INDEX_OVERLOAD(MY_MACRO, __VA_ARGS__)
 *  #define MY_MACRO0()        "Zero Args"
 *  #define MY_MACRO1(a)       "One Arg"
 *  #define MY_MACRO2(a, b)    "Two Args"
 *  #define MY_MACRO3(a, b, c) "Three Args"
 *  #define ...
 *
 */

// TODO: Finish