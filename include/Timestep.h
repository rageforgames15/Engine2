#pragma once
#include <chrono>

class Timestep
{
public:
  void NewTimeStep();
  float GetInSeconds();
  float GetInMilliseconds();
  std::chrono::duration<float> GetElapseTime();

  Timestep();
  ~Timestep() = default;
private:
  std::chrono::time_point<std::chrono::steady_clock> m_lastTimePoint;
};
