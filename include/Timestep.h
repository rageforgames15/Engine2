#pragma once
#include <chrono>

class Timestep
{
public:
  void NewTimeStep();
  float GetInSeconds();
  float GetInMilliseconds();

  Timestep();
  ~Timestep() = default;
private:
  std::chrono::time_point<std::chrono::steady_clock> m_lastTimePoint;
  float m_dt;
};
