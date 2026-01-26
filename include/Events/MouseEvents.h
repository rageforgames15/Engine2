#pragma once
#include "Events.h"

class MouseMovedEvent
  : public Event
{
public:
  double GetX() const {return m_x;}
  double GetY() const {return m_y;}

  MouseMovedEvent(double x, double y)
  : Event(EventType::MOUSE_MOVE), m_x(x), m_y(y)
  {}

private:
  double m_x, m_y;
};

class MouseButtonEvent
  : public Event
{
public:
  MouseButtonEvent(bool isLeft, EventType type)
    : Event(type), m_isLeft(isLeft)
  {}

  bool IsLeft() const {return m_isLeft;}
private:
  bool m_isLeft;
};

class MouseButtonPressedEvent
  : public MouseButtonEvent
{
public:
  MouseButtonPressedEvent(bool isLeftButton)
    : MouseButtonEvent(isLeftButton, EventType::MOUSE_BUTTON_PRESSED)
  {}
};

class MouseButtonReleasedEvent
  : public MouseButtonEvent
{
public:
  MouseButtonReleasedEvent(bool isLeftButton)
    : MouseButtonEvent(isLeftButton, EventType::MOUSE_BUTTON_RELEASED)
  {}
};
