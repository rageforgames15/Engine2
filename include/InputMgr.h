#pragma once
#include <GLFW/glfw3.h>

class InputManager
{
public:

  static InputManager& Get();

  InputManager(const InputManager&) = delete;
  void operator=(const InputManager&) = delete;
private:
  bool m_keys[GLFW_KEY_LAST];
};
