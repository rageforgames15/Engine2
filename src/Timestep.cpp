#include "Timestep.h"
#include <chrono>

std::chrono::duration<float> Timestep::GetElapseTime()
{
  auto currentTime = std::chrono::steady_clock::now();
  return currentTime - m_lastTimePoint;
}

void Timestep::NewTimeStep()
{
  m_lastTimePoint = std::chrono::steady_clock::now();
}

float Timestep::GetInMilliseconds()
{
  return static_cast<float>(
		std::chrono::duration_cast<std::chrono::milliseconds>
		(GetElapseTime()).count()
	);
}

float Timestep::GetInSeconds()
{
  return GetElapseTime().count();
}

Timestep::Timestep()
  : m_lastTimePoint(std::chrono::steady_clock::now())
{}
