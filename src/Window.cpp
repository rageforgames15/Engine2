#include "Window.h"
#include "Asserts.h"
#include "Events/Events.h"
#include "Events/WindowEvents.h"
#include "InputMgr.h"
#include <GLFW/glfw3.h>
#include <fmt/base.h>
#include <functional>
#include <string_view>

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

  GLFWwindow* window = glfwCreateWindow(
    settings.size.width,
    settings.size.height,
    settings.title.data(),
    nullptr,
    nullptr
  );

  // TODO: Error massage.
  if(!window)
    return nullptr;

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
  if(window && window->m_callback != nullptr)
  {
    WindowResizeEvent event(width, height);
    window->m_callback(event);
  }
}

void DefaultCloseEvent(GLFWwindow* glfwWindow)
{
  Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
  if(window && window->m_callback != nullptr)
  {
    WindowClosedEvent event;
    window->m_callback(event);
  }
}

void Window::SetTitle(std::string_view title)
{
  glfwSetWindowTitle(m_window, title.data());
}

void Window::ResizeWindow(const WindowSize& size)
{
  glfwSetWindowSize(m_window, size.width, size.height);
}

WindowSize Window::GetWindowSize()
{
  WindowSize size;
  glfwGetWindowSize(m_window, &size.width, &size.height);
  return size;
}

void Window::GetWindowSize(WindowSize& size)
{
  glfwGetWindowSize(m_window, &size.width, &size.height);
}

void Window::SetWindowEventCallback(EventCallbacker callback)
{
  m_callback = std::move(callback);
}

InputManager& Window::GetInputMgr()
{
  return m_inputManager;
}

void Window::SwapBuffer()
{
  glfwSwapBuffers(m_window);
}

void Window::MakeContext()
{
  glfwMakeContextCurrent(m_window);
}

bool Window::ShouldWindowClose()
{
  return glfwWindowShouldClose(m_window);
}

Window::Window(const WindowSettings& settings)
  : m_window(CreateWindow(settings))
{
  xengine_assert(m_window != nullptr);
  glfwSetWindowUserPointer(m_window, this);
  glfwSetFramebufferSizeCallback(m_window, DefaultResizeWindowCallback);
  glfwSetWindowCloseCallback(m_window, DefaultCloseEvent);
}

Window::~Window()
{
  glfwDestroyWindow(m_window);
}

