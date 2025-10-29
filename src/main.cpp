#include "Window.h"
#include <GLFW/glfw3.h>

int main()
{
  glfwInit();
  WindowSettings settings;
  settings.MSAA = 0;
  settings.minSize = {-1,-1};
  settings.size = {1280,720};
  settings.resizable = true;
  settings.title = "OpenGL";

  Window window(settings);
  while(!window.ShouldWindowClose())
  {
    glfwPollEvents();
    window.SwapBuffer();
  }
}
