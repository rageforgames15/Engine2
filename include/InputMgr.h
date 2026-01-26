#pragma once
#include "Events/Events.h"
#include <GLFW/glfw3.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4820)
#endif

class InputManager final
{
public:
  static InputManager& Get();

  bool IsKeyPressed(int key);
  void SetKeyState(int key, bool isPressed);

  void SetEventInputCallback(EventCallbacker callback);

  InputManager();
  ~InputManager();

  InputManager(const InputManager&) = delete;
  void operator=(const InputManager&) = delete;
  InputManager(InputManager&&) = delete;
  void operator=(InputManager&&) = delete;
private:
  bool m_keys[GLFW_KEY_LAST];
  EventCallbacker m_callbackFunction;
};

#ifdef _MSC_VER
#pragma warning(pop)
#endif