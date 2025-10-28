#include "InputMgr.h"
#include "Asserts.h"
#include <GLFW/glfw3.h>
#include <cstring>

static InputManager* s_InputManager;

bool InputManager::IsKeyPressed(int key)
{
  xengine_assert(key < GLFW_KEY_LAST);
  return m_keys[key];
}

void InputManager::SetKeyStatus(int key, bool isPressed)
{
  xengine_assert(key < GLFW_KEY_LAST);
  m_keys[key] = isPressed;
}

InputManager& InputManager::Get()
{
  xengine_assert(s_InputManager != nullptr);
  return *s_InputManager;
}

InputManager::InputManager()
{
  xengine_assert(s_InputManager != nullptr);
  s_InputManager = this;
  // Better if we know what everethihg is zero
  memset(&m_keys, 0, sizeof(m_keys));
}

InputManager::~InputManager()
{
  s_InputManager = nullptr;
}

