#pragma once
#include <GLFW/glfw3.h>
#include <string_view>
#include "Events/Events.h"
#include "InputMgr.h"

struct WindowSize final
{
  int32_t width;
  int32_t height;
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

  friend
  void DefaultMouseMoveEvent(
    GLFWwindow* glfwWindow,
    double xPos,
    double yPos
  );
  friend
  void DefaultFocusEvent(
    GLFWwindow* glfwWindow,
    int focused
  );

  friend
  void DefMouseButtonCallback(
    GLFWwindow* glfwwindow,
    int button,
    int action,
    int mods
  );

public:
  void SetTitle(std::string_view title);

  void ResizeWindow(const WindowSize& size);
  WindowSize GetWindowSize() const;
  void GetWindowSize(WindowSize& size) const;

  // Window resize, close, release, focused
  void SetWindowEventCallback(EventCallbacker callback);
 
  InputManager& GetInputMgr();
  void SwapBuffer() const;

  void MakeContext() const;

  bool ShouldWindowClose() const;
  bool IsFocused() const;

  void SetCursorPos(double xPos, double yPos) const;

  void LockCursor() const;
  void UnlockCursor() const;

  Window(const WindowSettings& settings);
  ~Window();

  Window(const Window&) = delete;
  void operator=(const Window&) = delete;
  Window(Window&&) = delete;
  void operator=(Window&&) = delete;
private:
  InputManager m_inputManager;
  EventCallbacker m_callback;
  GLFWwindow* m_window;
  bool m_isFocused;
};
