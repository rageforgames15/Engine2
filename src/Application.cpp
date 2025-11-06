#include "glad/gl.h"
#include "InputMgr.h"
#include "Events/MouseEvents.h"
#include "Timestep.h"
#include "Transform.h"
#include "Vertex.h"
#include "Window.h"
#include "Asserts.h"
#include "Events/Events.h"
#include "Events/EventDispatcher.h"
#include "Events/WindowEvents.h"
#include <Application.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "fmt/base.h"
#include <EnginePrint.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_int2x2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include "OpenGL/OpenGLShader.h"
#include "OpenGL/OpenGLBuffers.h"
#include "glm/ext.hpp"
#include "glm/glm.hpp"
#include "Camera.h"

Transform model;
Camera camera;

float lastMouseXPos{};
float lastMouseYPos{};

#define BIND(fn) std::bind(fn, this, std::placeholders::_1)

void DoMovement(float dt)
{
  InputManager& input = InputManager::Get();
  float movementSpeed = 5.f;

  Transform& view = camera.GetTransform();

  if(input.IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
    movementSpeed += 10.f;

  if(input.IsKeyPressed(GLFW_KEY_W))
    view.position += view.GetFowardVec() * movementSpeed * dt;
  if(input.IsKeyPressed(GLFW_KEY_S))
    view.position += view.GetFowardVec() * -movementSpeed * dt;
  if(input.IsKeyPressed(GLFW_KEY_A))
    view.position += view.GetRightVec() * -movementSpeed * dt;
  if(input.IsKeyPressed(GLFW_KEY_D))
    view.position += view.GetRightVec() * movementSpeed * dt;
}

void Application::Run()
{
  xengine_assert(m_running == false);
  Timestep time;
  m_running = true;

  model.position = glm::vec3(0,0,-6);

  OpenGLShader shader(
    "res/shaders/basic_vertex.vert",
    "res/shaders/basic_fragment.frag"
  ); 

  Vertex vertices[] = {
    // Передняя грань
    {glm::vec3(-1.0f, -1.0f,  1.0f)},  // 0: нижний левый перед
    {glm::vec3( 1.0f, -1.0f,  1.0f)},  // 1: нижний правый перед
    {glm::vec3( 1.0f,  1.0f,  1.0f)},  // 2: верхний правый перед
    {glm::vec3(-1.0f,  1.0f,  1.0f)},  // 3: верхний левый перед

    // Задняя грань
    {glm::vec3(-1.0f, -1.0f, -1.0f)},  // 4: нижний левый зад
    {glm::vec3( 1.0f, -1.0f, -1.0f)},  // 5: нижний правый зад
    {glm::vec3( 1.0f,  1.0f, -1.0f)},  // 6: верхний правый зад
    {glm::vec3(-1.0f,  1.0f, -1.0f)}   // 7: верхний левый зад
  };

  uint32_t indexis[] = {
    // Передняя грань
    0, 1, 2,
    2, 3, 0,
    // Задняя грань
    5, 4, 7,
    7, 6, 5,
    // Верхняя грань
    3, 2, 6,
    6, 7, 3,
    // Нижняя грань
    4, 5, 1,
    1, 0, 4,
    // Правая грань
    1, 5, 6,
    6, 2, 1,
    // Левая грань
    4, 0, 3,
    3, 7, 4
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

  vao.Unbind();

  ebo.Unbind();
  vbo.Unbind();

  shader.Use();

  glfwPollEvents();

  int32_t modelMatLoc{glGetUniformLocation(shader.GetID(),"u_modelMat")};
  int32_t viewMatLoc{glGetUniformLocation(shader.GetID(),"u_viewMat")};
  int32_t projMatLoc{glGetUniformLocation(shader.GetID(),"u_projMat")};
  m_window.LockCursor();

  while(IsRunning())
  {
    m_window.SwapBuffer();

    time.NewTimeStep();
    float dt = time.GetInSeconds();
    float fps = 1 / time.GetInSeconds();
    m_window.SetTitle(std::to_string(fps));
    DoMovement(dt);
    WindowSize windowSize = m_window.GetWindowSize();
    glm::mat4 projection = glm::perspective<float>(
      45.f,
      windowSize.width / (float)windowSize.height,
      0.1f,
      100.f
    );

    glUniformMatrix4fv(modelMatLoc,1,GL_FALSE, glm::value_ptr(model.ToMatrix()));
    glUniformMatrix4fv(viewMatLoc,1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));
    glUniformMatrix4fv(projMatLoc,1, GL_FALSE, glm::value_ptr(projection));

    vao.Bind();
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    // Render here
    // And layers ))
    //xengine_print("CTF:\n Pos:{},{},{}\nRot:{},{},{}\n",view.position.x,view.position.y,view.position.z,view.rotation.x,view.rotation.y,view.rotation.z);
    vao.Unbind();

    glfwPollEvents();
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

bool Application::OnMouseMove(const MouseMovedEvent& event)
{
  float newXPos = event.GetX();
  float newYPos = event.GetY();
  float elapseXPos = lastMouseXPos - newXPos;
  float elapseYPos = newYPos - lastMouseYPos;

  Transform& view = camera.GetTransform();

  lastMouseXPos = newXPos;
  lastMouseYPos = newYPos;

  view.rotation.x += elapseYPos * 0.15f;
  view.rotation.y += elapseXPos * 0.15f;

  if(view.rotation.x > 89.f)
    view.rotation.x = 89.f;
  else if(view.rotation.x < -89.f)
    view.rotation.x = -89.f;

  return true;
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

  dispatcher.Dispatch<
    EventType::MOUSE_MOVE,
    MouseMovedEvent> (BIND(&Application::OnMouseMove));

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

