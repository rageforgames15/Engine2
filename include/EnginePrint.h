#pragma once
#include <fmt/base.h>

#ifndef PRODUCT_BUILD

#define xengine_println(...) fmt::println(__VA_ARGS__)
#define xengine_print(...) fmt::print(__VA_ARGS__)

#else

#define xengine_println(...)
#define xengine_print(...)

#endif

