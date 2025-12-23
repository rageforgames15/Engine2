#pragma once
#include "Timestep.h"
#include <string_view>
#include <string>

void _start_profile(std::string_view name);
void _end_profile(std::string_view name);

#ifndef PRODUCT_BUILD
#define XENGINE_START_PROFILE(name) _start_profile(name)
#define XENGINE_END_PROFILE(name) _end_profile(name)
#else
#define XENGINE_START_PROFILE(name)
#define XENGINE_END_PROFILE(name)
#endif