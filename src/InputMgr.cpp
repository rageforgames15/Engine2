#include "InputMgr.h"
#include "Asserts.h"
#include "Events/Events.h"
#include "Events/InputEvents.h"
#include <GLFW/glfw3.h>
#include <cstring>
#include <fmt/base.h>
#include <utility>

static InputManager* s_InputManager = nullptr;

bool InputManager::IsKeyPressed(int key)
{
  xengine_assert(key < GLFW_KEY_LAST);
  return m_keys[key];
}

void InputManager::SetKeyState(int key, bool isPressed)
{
  xengine_assert(key < GLFW_KEY_LAST);
  m_keys[key] = isPressed;

  if(isPressed)
  {
    KeyPressedEvent event(key);
    m_callbackFunction(event);
  }
  else
  {
    KeyReleasedEvent event(key);
    m_callbackFunction(event);
  }
}

InputManager& InputManager::Get()
{
  xengine_assert(s_InputManager != nullptr);
  return *s_InputManager;
}

InputManager::InputManager()
{
  xengine_assert(s_InputManager == nullptr);
  s_InputManager = this;
  // Better if we know what everethihg is zero
  memset(&m_keys, 0, sizeof(m_keys));
}

InputManager::~InputManager()
{
  s_InputManager = nullptr;
}

void InputManager::SetEventInputCallback(EventCallbacker callback)
{
  m_callbackFunction = std::move(callback);
}

