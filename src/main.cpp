#include "Application.h"
#include "EnginePrint.h"
#include "Window.h"
#include <GLFW/glfw3.h>
#include <filesystem>
#include "FileLogger.h"
#include "FileIO.h"
#include <utility>
#include "Profile.h"
#include "Asserts.h"

int main()
{
  // THIS SHOULD LIVE ENTIRE PROGRAM, DONT PUT IT TO APPLICATION
  XENGINE_START_PROFILE("Init engine");
  FileLogger logger(false);
  glfwInit();

  ApplicationSpecific settings;
  settings.windowSettings = {
    .title = "Engine",
    .size = {512,512},
    .minSize = {0, 0},
    .MSAA = 0,
    .resizable = true
  };

  Application app(settings);
  XENGINE_END_PROFILE("Init engine");
  app.Run();
  return 0; 
}
