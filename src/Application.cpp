#include "Vertex.h"
#include "glad/gl.h"
#include "Asserts.h"
#include "Events/Events.h"
#include "Events/EventDispatcher.h"
#include "Events/WindowEvents.h"
#include <Application.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "fmt/base.h"
#include <EnginePrint.h>
#include "OpenGL/OpenGLShader.h"
#include "OpenGL/OpenGLBuffers.h"

#define BIND(fn) std::bind(fn, this, std::placeholders::_1)

void Application::Run()
{
  xengine_assert(m_running == false);
  m_running = true;

  OpenGLShader shader(
    "res/shaders/basic_vertex.vert",
    "res/shaders/basic_fragment.frag"
  );
  Vertex vertices[] = {
    {glm::vec3(-0.5f, -0.5f, 0.0f)}, // нижний правый угол
    {glm::vec3(0.5f, -0.5f, 0.0f)}, // нижний левый угол
    {glm::vec3(0.5f, 0.5f, 0.0f)}, // верхний левый угол
    {glm::vec3(-0.5f, 0.5f, 0.0f)} // верхний правый угол
  };

  uint32_t indexis[] = {
    0,1,3,
    1,2,3
  };

  OpenGLVAO vao;
  vao.Bind();
  OpenGLVBO vbo;
  vbo.Bind();
  OpenGLEBO ebo;
  ebo.Bind();

  vbo.SetData(vertices, sizeof(vertices), GL_STATIC_DRAW);
  vbo.SetAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

  ebo.SetData(indexis, sizeof(indexis), GL_STATIC_DRAW);

  shader.Use();

  vao.Unbind();
  ebo.Unbind();
  vbo.Unbind();

  // Window tiling manager fix
  m_window.SwapBuffer();

  while(IsRunning())
  {
    glfwPollEvents();

    vao.Bind();
    //ebo.Bind();
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Render here
    // And layers ))

    vao.Unbind();

    m_window.SwapBuffer();
  }
}

bool Application::OnWindowResize(const WindowResizeEvent& event)
{
  glViewport(0, 0, event.GetWidth(), event.GetHeight());
  xengine_print(
    "New window size. Width {}, Height {}\n",
    event.GetWidth(),
    event.GetHeight()
  );

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

