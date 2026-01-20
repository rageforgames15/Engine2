#include "glad/gl.h"
#include "Events/Events.h"
#include "Events/EventDispatcher.h"
#include "Events/MouseEvents.h"
#include "Application.h"
#include "MacroUtils.h"
#include "Timestep.h"
#include "Events/ApplicationEvents.h"
#include "FileLogger.h"
#include "AppLayer.h"
#include <thread>
#include <chrono>
#include "EnginePrint.h"

static FileLogger s_logger{false};

void Application::OnEvent(Event& event)
{
  for(auto it = m_layerStack.begin(); it != m_layerStack.end(); ++it)
  {
      it->get()->OnEvent(event);
  }
  EventDispatcher dispatcher(event);
  dispatcher.Dispatch
  <EventType::WINDOW_RESIZED, WindowResizeEvent>
  (BIND(&Application::OnWindowResize));

  dispatcher.Dispatch
  <EventType::WINDOW_CLOSED, WindowClosedEvent>
  (BIND(&Application::OnWindowClose));

  dispatcher.Dispatch
  <EventType::MOUSE_MOVE, MouseMovedEvent>
  (BIND(&Application::OnMouseMove));
}

void Application::Run()
{
  if(m_running) return;
  m_running = true;
  Timestep dtStep;
  float dt{0.f};
  DrawData drawData{};
  m_layerStack.PushToLayerStack<AppLayer>();
  
  /*
  PipeLine:
    Calculate DT
    PollEvents
    ClearBuffers
    Update drawdata
    Render:
      Render Layers
    Update Layers
    Update scripts (WIP)
    SwapBuffers
    Proced layer queue transitions (WIP)
  */

  while (m_running)
  {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    WindowSize wndSize = m_window.GetWindowSize();
    drawData.height = wndSize.height;
    drawData.width = wndSize.width;
    for(auto it = m_layerStack.begin(); it != m_layerStack.end(); ++it)
    {
      it->get()->Draw(drawData);
    }
    ApplcationTickEvent updateEvent(dt);
    OnEvent(updateEvent);
    m_window.SwapBuffer();
    dt = dtStep.GetInSeconds();
    dtStep.NewTimeStep();
  }
}

bool Application::OnWindowResize(const WindowResizeEvent& event)
{
  glViewport(0,0,event.GetWidth(), event.GetHeight());
  return true;
}

bool Application::OnWindowClose([[maybe_unused]] const WindowClosedEvent& event)
{
  Stop();
  return true;
}

bool Application::OnMouseMove([[maybe_unused]] const MouseMovedEvent& event)
{
  return true;
}

void Application::Stop()
{
  m_running = false;
}

Application::Application(
  const ApplicationSpecific& specific
) : m_window(specific.windowSettings),
    m_running(false)
{
  m_window.MakeContext();
  m_window.SetWindowEventCallback(BIND(&Application::OnEvent));
  if(!gladLoadGL(glfwGetProcAddress))
    XELogger::ErrorAndCrash("Failed to initialize glad");
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_DEPTH_TEST);
}
