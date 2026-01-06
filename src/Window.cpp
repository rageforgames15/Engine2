#include "Window.h"
#include "Asserts.h"
#include "Events/Events.h"
#include "Events/MouseEvents.h"
#include "Events/WindowEvents.h"
#include "InputMgr.h"
#include <GLFW/glfw3.h>
#include <fmt/base.h>
#include <functional>
#include <string_view>
#include "FileLogger.h"

void glfwError(int code, const char* desc)
{
  fmt::print("Code: {}, Desc: {}", code, desc);
}

GLFWwindow* CreateWindow(
  const WindowSettings& settings
)
{
  glfwSetErrorCallback(glfwError);
  glfwWindowHint(GLFW_RESIZABLE, settings.resizable);
  glfwWindowHint(GLFW_SAMPLES, settings.MSAA);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(
    settings.size.width,
    settings.size.height,
    settings.title.data(),
    nullptr,
    nullptr
  );

  if(!window)
  {
    // Anyway, we have only 1 window
    XELogger::ErrorAndCrash("Failed to create window");
    return nullptr; // never call
  }

  glfwSetWindowSizeLimits(
    window,
    settings.minSize.width,
    settings.minSize.height,
    GLFW_DONT_CARE, GLFW_DONT_CARE
  );

  return window;
}

void DefaultResizeWindowCallback(
  GLFWwindow* glfwWindow,
  int width,
  int height
)
{
  Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
  if(window->m_callback != nullptr)
  {
    WindowResizeEvent event(width, height);
    window->m_callback(event);
  }
}

void DefaultCloseEvent(GLFWwindow* glfwWindow)
{
  Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
  if(window->m_callback != nullptr)
  {
    WindowClosedEvent event;
    window->m_callback(event);
  }
}

void DefaultMouseMoveEvent(
  GLFWwindow* glfwWindow,
  double xPos,
  double yPos
)
{
  Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
  if(window->m_callback != nullptr)
  {
    MouseMovedEvent event(xPos,yPos);
    window->m_callback(event);
  }
}

void DefaultKeyWindowEvent(
  GLFWwindow* glfwWindow,
  int key,
  [[maybe_unused]] int scanMode,
  [[maybe_unused]] int action,
  [[maybe_unused]] int mods
)
{
  Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
  if(action == GLFW_PRESS)
    window->GetInputMgr().SetKeyState(key, true);
  else if(action == GLFW_RELEASE)
    window->GetInputMgr().SetKeyState(key, false);
}

void DefaultFocusEvent(
  GLFWwindow* glfwWindow,
  int focused
)
{
  Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
  window->m_isFocused = focused;
  if(window->m_callback != nullptr)
  {
    if(focused)
    {
      WindowFocusedEvent event;
      window->m_callback(event);
    }
    else
    {
      WindowReleaseEvent event;
      window->m_callback(event);
    }
  }
}

bool Window::IsFocused() const
{
  return m_isFocused;
}

void Window::SetTitle(std::string_view title)
{
  glfwSetWindowTitle(m_window, title.data());
}

void Window::ResizeWindow(const WindowSize& size)
{
  glfwSetWindowSize(m_window, size.width, size.height);
}

WindowSize Window::GetWindowSize() const
{
  WindowSize size;
  glfwGetWindowSize(m_window, &size.width, &size.height);
  return size;
}

void Window::GetWindowSize(WindowSize& size) const
{
  glfwGetWindowSize(m_window, &size.width, &size.height);
}

void Window::SetWindowEventCallback(EventCallbacker callback)
{
  m_inputManager.SetEventInputCallback(callback);
  m_callback = callback;
}

InputManager& Window::GetInputMgr()
{
  return m_inputManager;
}

void Window::SwapBuffer() const
{
  glfwSwapBuffers(m_window);
}

void Window::MakeContext() const
{
  glfwMakeContextCurrent(m_window);
}

bool Window::ShouldWindowClose() const
{
  return glfwWindowShouldClose(m_window);
}

void Window::SetCursorPos(double xPos, double yPos) const
{
  glfwSetCursorPos(m_window, xPos, yPos);
}

void Window::LockCursor() const
{
  glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::UnlockCursor() const
{
  glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

Window::Window(const WindowSettings& settings)
  : m_window(CreateWindow(settings)),
    m_isFocused(true)
{
  glfwSetWindowUserPointer(m_window, this);
  glfwSetWindowFocusCallback(m_window, DefaultFocusEvent);
  glfwSetFramebufferSizeCallback(m_window, DefaultResizeWindowCallback);
  glfwSetWindowCloseCallback(m_window, DefaultCloseEvent);
  glfwSetKeyCallback(m_window, DefaultKeyWindowEvent);
  glfwSetCursorPosCallback(m_window, DefaultMouseMoveEvent);
  glfwFocusWindow(m_window);
}

Window::~Window()
{
  glfwDestroyWindow(m_window);
}
