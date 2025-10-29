#pragma once

#include "Events.h"

class KeyEvent 
  : public Event
{
public:
  const int GetKey() const {return m_key;}

  KeyEvent(int key, EventType eventType)
    : m_key(key), Event(eventType)
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
