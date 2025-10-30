#include "glad/gl.h"
#include "Asserts.h"
#include "Events/Events.h"
#include "Events/EventDispatcher.h"
#include "Events/WindowEvents.h"
#include <Application.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "fmt/base.h"
#include <EnginePrint.h>

#define BIND(fn) std::bind(fn, this, std::placeholders::_1)

void Application::Run()
{
  xengine_assert(m_running == false);
  m_running = true;

  while(IsRunning())
  {
    glfwPollEvents();

    // Render here
    // And layers :)

    m_window.SwapBuffer();
  }
}

bool Application::OnWindowResize(const WindowResizeEvent& event)
{
  glViewport(0, 0, 1280, 720);
  xengine_print("New window size. Width {}, Height {}\n", event.GetWidth(), event.GetHeight());

  return true;
}

bool Application::OnWindowClose(const WindowClosedEvent& event)
{
  Stop();
  return true;
}

bool Application::IsRunning() const
{
  return m_running;
}

void Application::Stop()
{
  m_running = false;
}

void Application::OnEvent(Event& event)
{
  EventDispatcher dispatcher(event);
  dispatcher.Dispatch<
    EventType::WINDOW_RESIZED,
    WindowResizeEvent> (BIND(&Application::OnWindowResize));

  dispatcher.Dispatch<
    EventType::WINDOW_CLOSED,
    WindowClosedEvent> (BIND(&Application::OnWindowClose));

  xengine_print("Event was dispatched\n");
}

Application::Application(ApplicationSpecific& spec)
  : m_window(spec.windowSettings), m_running(false)
{
  m_window.SetWindowEventCallback(
    std::bind(&Application::OnEvent, this, std::placeholders::_1)
  );

  m_window.MakeContext();
  gladLoadGL(glfwGetProcAddress);
}

