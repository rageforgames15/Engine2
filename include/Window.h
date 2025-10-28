#pragma once
#include <cstdint>
#include <string_view>

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
  void SetEventCallback();

  Window(const WindowSettings& settings);
  ~Window();
private:
  WindowSettings settings;
};

