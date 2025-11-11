#include "Application.h"
#include "EnginePrint.h"
#include "Window.h"
#include <GLFW/glfw3.h>
#include <filesystem>

int main()
{
  glfwInit();

  // Debugger thing,
  xengine_print("Current working directory {}\n", std::filesystem::current_path().c_str());

  ApplicationSpecific settings;
  settings.windowSettings = {
    .title = "Engine",
    .size = {1280,720},
    .minSize = {640, 480},
    .MSAA = 0,
    .resizable = true,
  };

  Application app(settings);
  app.Run();
  return 0;
}
