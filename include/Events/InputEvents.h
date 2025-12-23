#pragma once

#include "Events.h"

class KeyEvent 
  : public Event
{
public:
  int GetKey() const {return m_key;}

  KeyEvent(int key, EventType eventType)
    : Event(eventType), m_key(key)
  {}

private:
  const int m_key;
};

class KeyPressedEvent 
  : public KeyEvent
{
public:
  KeyPressedEvent(int key)
    : KeyEvent(key, EventType::KEY_PRESSED)
  {}
};

class KeyReleasedEvent
  : public KeyEvent
{
public:
  KeyReleasedEvent(int key)
    : KeyEvent(key, EventType::KEY_RELEASED)
  {}
};
