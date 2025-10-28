#pragma once
#include <functional>
#include "Events/Events.h"

class EventDispatcher
{
public:
  EventDispatcher(Event& event) : event(event) {}

  template<EventType Type = EventType::NONE, typename FnEvent>
  void Dispatch(std::function<bool(const FnEvent&)> fn)
  {
    if(!event.ishandled && Type == event.type)
    {
      event.ishandled = fn(static_cast<const FnEvent&>(event)) || false;
    }
  }

private:
  Event& event;
};
