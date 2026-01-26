#pragma once
#include <cstdint>
#include <functional>

class EventDispatcher;

enum class EventType : uint8_t
{
  NONE = 0,
  WINDOW_RESIZED, WINDOW_RELEASED, WIDNOW_FOCUSED, WINDOW_CLOSED,
  KEY_PRESSED, KEY_RELEASED,
  MOUSE_MOVE, MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED,
  APP_TICK
};

class Event
{
public:
  friend class EventDispatcher;
public:
  EventType GetType() const {return m_type;}

  Event(const EventType type)
  : m_type(type), m_ishandled(false)
  {}
  ~Event() = default;
private:
  const EventType m_type = EventType::NONE;
  bool m_ishandled = false;
};

typedef std::function<void(Event&)> EventCallbacker;
