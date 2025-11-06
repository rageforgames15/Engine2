#pragma once
#include "Events/Events.h"
#include "Events/WindowEvents.h"
#include "Events/MouseEvents.h"
#include "Window.h"

struct ApplicationSpecific
{
  WindowSettings windowSettings;
};

class Application
{
public:
  void OnEvent(Event& event);
  void Run();

  bool OnWindowResize(const WindowResizeEvent& event);
  bool OnWindowClose(const WindowClosedEvent& event);
  bool OnMouseMove(const MouseMovedEvent& event);
  bool IsRunning() const;
  void Stop();

  Application(ApplicationSpecific& specific);
  ~Application() = default;
private:
  Window m_window;
  bool m_running;
};
