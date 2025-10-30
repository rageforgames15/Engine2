#pragma once
#include <GLFW/glfw3.h>
#include <string_view>
#include "Events/Events.h"
#include "InputMgr.h"

struct WindowSize final
{
  int width;
  int height;
};

struct WindowSettings final
{
  std::string_view title;
  WindowSize size = {1280, 720};
  WindowSize minSize = {-1,-1};
  int MSAA = 0;
  bool resizable = true;
};

class Window final
{
public:
  friend
  void DefaultResizeWindowCallback(
    GLFWwindow* glfwWindow,
    int width,
    int height
  );

  friend
  void DefaultCloseEvent(GLFWwindow* window);

public:
  void SetTitle(std::string_view title);

  void ResizeWindow(const WindowSize& size);
  WindowSize GetWindowSize();
  void GetWindowSize(WindowSize& size);

  // Window resize, close, release, focused
  void SetWindowEventCallback(EventCallbacker callback);
 
  InputManager& GetInputMgr();
  void SwapBuffer();

  void MakeContext();

  bool ShouldWindowClose();

  Window(const WindowSettings& settings);
  ~Window();
private:
  InputManager m_inputManager;
  GLFWwindow* m_window;
  EventCallbacker m_callback;
};

