#pragma once
#include "Events.h"

class MouseMovedEvent 
  : public Event
{
  float GetX() {return m_x;}
  float GetY() {return m_y;}

  MouseMovedEvent(float x, float y)
  : Event(EventType::MOUSE_MOVE), m_x(x), m_y(y)
  {}

private:
  float m_x, m_y;
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

class MouseButtonReleased
  : public MouseButtonEvent
{
public:
  MouseButtonReleased(bool isLeftButton)
    : MouseButtonEvent(isLeftButton, EventType::MOUSE_BUTTON_RELEASED)
  {}
};

