#pragma once
#include <functional>
#include "Events/Events.h"

class EventDispatcher
{
public:
  EventDispatcher(Event& event) : m_event(event) {}

  template<EventType Type = EventType::NONE, typename FnEvent>
  void Dispatch(std::function<bool(const FnEvent&)> fn)
  {
    if(!m_event.m_ishandled && Type == m_event.m_type)
    {
      m_event.m_ishandled = fn((const FnEvent&)m_event);
    }
  }

  template<EventType Type = EventType::NONE, typename FnEvent>
  void VoidDispatch(std::function<void(const FnEvent&)> fn)
  {
    if(!m_event.m_ishandled && Type == m_event.m_type)
    {
      fn((const FnEvent&)m_event);
    }
  }

private:
  Event& m_event;
};
