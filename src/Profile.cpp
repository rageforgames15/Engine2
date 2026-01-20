#include "Profile.h"
#include "Timestep.h"
#include "Asserts.h"
#include "EnginePrint.h"
#include <unordered_map>
#include <string>
#include <chrono>

static std::unordered_map<
  std::string_view, Timestep
> s_timesteps;

void _start_profile([[maybe_unused]] std::string_view name)
{
#ifndef PRODUCT_BUILD
  s_timesteps.emplace(name, Timestep{});
#endif
}

void _end_profile([[maybe_unused]] std::string_view name)
{
#ifndef PRODUCT_BUILD
  xengine_assert(s_timesteps.contains(name));
  float time = s_timesteps.at(name).GetInMilliseconds();
  s_timesteps.erase(name);
  xengine_print("{} was completed in {}ms\n",name,time);
#endif
}