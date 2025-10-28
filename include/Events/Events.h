#pragma once
#include <cstdint>

class EventDispatcher;

enum class EventType : uint8_t
{
  NONE = 0,
  WINDOW_RESIZED, WINDOW_RELEASED, WIDNOW_FOCUSED, WINDOW_CLOSED,
  KEY_PRESSED, KEY_RELEASED,
  MOUSE_MOVE, MOUSE_BUTTON_PRESSED,
  APP_TICK
};

class Event
{
public:
  friend class EventDispatcher;
public:
  const EventType GetType() const {return type;}

  Event(const EventType type)
  : ishandled(false), type(type)
  {}
  ~Event() = default;
private:
  const EventType type;
  bool ishandled;
};

