#pragma once
#include "Events.h"

class WindowResizeEvent : public Event
{
public:
  WindowResizeEvent(int width, int height) 
    : Event(EventType::WINDOW_RESIZED),
    width(width),
    height(height)
  {}

  int GetWidth() const {return width;}
  int GetHeight() const {return height;}

private:
  int width, height;
};

class WindowClosedEvent : public Event
{
public:
  WindowClosedEvent() : Event(EventType::WINDOW_CLOSED) {}
};
