#pragma once
#include "Events/Events.h"


// TODO: Make getter for dt
class ApplcationTickEvent : public Event
{
public:
  ApplcationTickEvent(float dt)
    : Event(EventType::APP_TICK), dt(dt)
    {}
  float dt;
};