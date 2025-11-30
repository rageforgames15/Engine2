#include "Timestep.h"
#include <chrono>

void Timestep::NewTimeStep()
{
  auto currentTime = std::chrono::steady_clock::now();
  auto elapseTime = currentTime - m_lastTimePoint;
  m_lastTimePoint = currentTime;

  m_dt = std::chrono::duration<float>(elapseTime).count();
}

float Timestep::GetInMilliseconds()
{
  return m_dt * 1000;
}

float Timestep::GetInSeconds()
{
  return m_dt;
}

Timestep::Timestep()
  : m_lastTimePoint(std::chrono::steady_clock::now())
{}
