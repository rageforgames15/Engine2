#pragma once
#include "Events.h"

class WindowResizeEvent 
  : public Event
{
public:
  WindowResizeEvent(int width, int height) 
    : Event(EventType::WINDOW_RESIZED),
    m_width(width),
    m_height(height)
  {}

  int GetWidth() const {return m_width;}
  int GetHeight() const {return m_height;}

private:
  int m_width, m_height;
};

class WindowClosedEvent
  : public Event
{
public:
  WindowClosedEvent() : Event(EventType::WINDOW_CLOSED) {}
};
