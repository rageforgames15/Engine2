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
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <iostream>
#include <string>
#include "OpenGL/OpenGLShader.h"
#include "OpenGL/OpenGLBuffers.h"
#include "glm/ext.hpp"
#include "glm/glm.hpp"
#include "Camera.h"
#include "OpenGL/OpenGLTexture.h"
#include <cstddef>
#include "Lua/Lua.h"
#include <print>

Transform model;
Transform model2;
Transform model3;
Camera camera;

int l_print(sol::variadic_args data, sol::this_state L)
{
  fmt::print("[LUA]");
  sol::state_view lua{L};
  sol::function tostrFun = lua["tostring"];
  for(auto val : data)
  {
    sol::safe_function_result res = tostrFun(val);
    if(!res.valid()) continue;
    sol::object str_obj{res};
    fmt::print("{} ", str_obj.as<std::string>());
  }
  fmt::print("\n");
  return 0;
}


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
  if(input.IsKeyPressed(GLFW_KEY_Q))
    camera.SetFov(camera.GetFov() + 25 * dt);
  if(input.IsKeyPressed(GLFW_KEY_E))
    camera.SetFov(camera.GetFov() - 25 * dt);
  if(input.IsKeyPressed(GLFW_KEY_LEFT_CONTROL))
    view.position.y -= movementSpeed * dt;
  if(input.IsKeyPressed(GLFW_KEY_SPACE))
    view.position.y += movementSpeed * dt;

  camera.SetFov(std::clamp(camera.GetFov(), 10.f, 179.f));
}

void Application::Run()
{
  xengine_assert(m_running == false);
  Timestep time;
  m_running = true;

  model.position = glm::vec3(0,3,-6);
  model2.position = glm::vec3(0,-3,-6);
  model3.position = glm::vec3(0,0,-6);

  OpenGLShader shader(
    "res/shaders/basic_vertex.vert",
    "res/shaders/basic_fragment.frag"
  ); 

  Vertex vertices[] = {
    {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)},
    {glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f)},
    {glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)},
    {glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)},
    {glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f)},
    {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f)},

    {glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)},
    {glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)},
    {glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 1.0f)},
    {glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 1.0f)},
    {glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 1.0f)},
    {glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)},

    {glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)},
    {glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)},
    {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)},
    {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)},
    {glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)},
    {glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)},

    {glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)},
    {glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)},
    {glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)},
    {glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)},
    {glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)},
    {glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)},

    {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)},
    {glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f)},
    {glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)},
    {glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f)},
    {glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f)},
    {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f)},

    {glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f)},
    {glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f)},
    {glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)},
    {glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f)},
    {glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 0.0f)},
    {glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f)}
  };

  OpenGLVAO vao;
  vao.Bind();
  OpenGLVBO vbo;
  vbo.Bind();

  vbo.SetData(vertices, sizeof(vertices), GL_STATIC_DRAW);
  vbo.SetAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  vbo.SetAttribute(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, uvPos));

  vao.Unbind();
  vbo.Unbind();

  shader.Use();

  glfwPollEvents();

  int32_t modelMatLoc{glGetUniformLocation(shader.GetID(),"u_modelMat")};
  int32_t viewMatLoc{glGetUniformLocation(shader.GetID(),"u_viewMat")};
  int32_t projMatLoc{glGetUniformLocation(shader.GetID(),"u_projMat")};
  m_window.LockCursor();

  OpenGLTexture wood("res/images/wood.jpg", GL_TEXTURE_2D);
  OpenGLTexture face("res/images/face.png", GL_TEXTURE_2D);
  //wood.BindTexture(0, GL_TEXTURE_2D);

  sol::state lua;
  lua.open_libraries(
    sol::lib::base,
    sol::lib::bit32,
    sol::lib::coroutine,
    sol::lib::string,
    sol::lib::jit,
    sol::lib::ffi
  );
  lua["print"] = &l_print;
  sol::protected_function_result res =  lua.do_file("res/lua/main.lua");
  while(IsRunning())
  {
    m_window.SwapBuffer();
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    float dt = time.GetInSeconds();
    float fps = 1 / time.GetInSeconds();
    m_window.SetTitle(std::to_string(fps));
    DoMovement(dt);
    WindowSize windowSize = m_window.GetWindowSize();
    
    glm::mat4 projection = glm::perspective<float>(
      glm::radians(camera.GetFov()),
      windowSize.width / (float)windowSize.height,
      0.025f,
      100.f
    );
    
    model.rotation.x += 90.f * dt;
    model.rotation.y += 45.f * dt;
    
    model2.rotation.x += 45.f * dt;
    model2.rotation.y += 90.f * dt;

    model3.rotation.x += 45.f * dt;
    model3.rotation.y += 45.f * dt;
    //camera.GetTransform().rotation.z += 90.f * dt;
    glUniformMatrix4fv(modelMatLoc,1,GL_FALSE, glm::value_ptr(model.ToMatrix()));
    glUniformMatrix4fv(viewMatLoc,1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));
    glUniformMatrix4fv(projMatLoc,1, GL_FALSE, glm::value_ptr(projection));
    
    vao.Bind();
    wood.BindTexture(0);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUniform1i(glGetUniformLocation(shader.GetID(),"u_tex"), 0);
    glDrawArrays(GL_TRIANGLES,0,36);

    glUniformMatrix4fv(modelMatLoc,1,GL_FALSE,glm::value_ptr(model2.ToMatrix()));
    glDrawArrays(GL_TRIANGLES,0,36);

    face.BindTexture(0);
    glUniformMatrix4fv(modelMatLoc,1,GL_FALSE,glm::value_ptr(model3.ToMatrix()));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // Render here
    // And layers ))
    //xengine_print("CTF:\n Pos:{},{},{}\nRot:{},{},{}\n",view.position.x,view.position.y,view.position.z,view.rotation.x,view.rotation.y,view.rotation.z);
    vao.Unbind();
    
    glfwPollEvents();
    time.NewTimeStep();
  }
}

bool Application::OnWindowResize(const WindowResizeEvent& event)
{
  glViewport(0, 0, event.GetWidth(), event.GetHeight());
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

  view.rotation.x -= elapseYPos * 0.125f;
  view.rotation.y += elapseXPos * 0.125f;

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
}

Application::Application(ApplicationSpecific& spec)
  : m_window(spec.windowSettings), m_running(false)
{
  m_window.SetWindowEventCallback(
    std::bind(&Application::OnEvent, this, std::placeholders::_1)
  );

  m_window.MakeContext();
  gladLoadGL(glfwGetProcAddress);
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_DEPTH_TEST);
}

