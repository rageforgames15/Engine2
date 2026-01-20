#pragma once
#include "Events/Events.h"
#include "Events/WindowEvents.h"
#include "Events/MouseEvents.h"
#include "Window.h"
#include "LayerStack.h"

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
  void Stop();

  Application(const ApplicationSpecific& specific);
  virtual ~Application() = default;

  Application(const Application&) = delete;
  void operator=(const Application&) = delete;
  Application(Application&&) = delete;
  void operator=(Application&&) = delete;

private:

  Window m_window;
  LayerStack m_layerStack;
  bool m_running;
};
