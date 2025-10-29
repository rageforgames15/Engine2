#pragma once
#include "Events/Events.h"
#include "Window.h"

struct ApplicationSpecific
{
  WindowSettings WindowSettings; // 8 bytes
};

class Application
{
public:
  void OnEvent(const Event& event);

  void Run();

  Application(ApplicationSpecific& specific);
  ~Application() = default;
private:
  Window window;
};
