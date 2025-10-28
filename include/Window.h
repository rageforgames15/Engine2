#pragma once
#include <cstdint>
#include <string_view>
#include "InputMgr.h"

struct WindowSettings
{
  std::string_view title;
  int32_t height;
  int32_t width;
};

class Window
{
public:
  void SetTitle(std::string_view title);
  std::string_view GetTitle() const;

  // Window resize, close, release, focused
  void SetWindowEventCallback();

  InputManager& GetInputMgr();

  Window(const WindowSettings& settings);
  ~Window();
private:
  InputManager m_inputManager;
  WindowSettings m_settings;
};

