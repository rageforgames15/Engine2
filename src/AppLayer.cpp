#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "InputMgr.h"
#include "AppLayer.h"
#include "Events/EventDispatcher.h"
#include "Events/ApplicationEvents.h"
#include "MacroUtils.h"
#include "Vertex.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "EnginePrint.h"
#include "Asserts.h"
#include <filesystem>

static float s_time{};

void AppLayer::updateTextureIndex()
{
	m_currentTextureIndex = (m_currentTextureIndex + 1) % m_textures.size();
	s_time = 0;
	fmt::println("Current index is {}", m_currentTextureIndex);
}

void AppLayer::OnEvent(Event& event)
{
  EventDispatcher dispatch{event};
  dispatch.VoidDispatch<
    EventType::APP_TICK,
    ApplcationTickEvent
  >(BIND(&AppLayer::OnTick));
  dispatch.VoidDispatch<
    EventType::MOUSE_BUTTON_PRESSED,
    MouseButtonPressedEvent
  >(BIND(&AppLayer::OnMousePress));
}

void AppLayer::OnAttach()
{}

void AppLayer::OnDetach()
{}

void AppLayer::Draw(const DrawData& data)
{
  m_vao.Bind();
  m_shader.Use();
	m_textures[m_currentTextureIndex].BindTexture(0);
  glm::mat4 mvp
    = glm::perspective(
      glm::radians(m_camera.GetFov()),
      static_cast<float>(data.width) / data.height,
      0.01f, 1000.f
    ) * m_camera.GetViewMatrix() * m_cube.ToMatrix();
  glUniformMatrix4fv(
    glGetUniformLocation(m_shader.GetID(),"u_mvp"),
    1, GL_FALSE, glm::value_ptr(mvp)
  );
  glUniform1i(glGetUniformLocation(m_shader.GetID(), "u_tex"),0);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  m_vbo.Unbind();
}

void AppLayer::OnTick(const ApplcationTickEvent& event)
{
/*  InputManager& inputManager = InputManager::Get();
  if(inputManager.IsKeyPressed(GLFW_KEY_W))
    m_cube.rotation.x -= 90.f * event.dt;
  if(inputManager.IsKeyPressed(GLFW_KEY_S))
    m_cube.rotation.x += 90.f * event.dt;
  if(inputManager.IsKeyPressed(GLFW_KEY_A))
    m_cube.rotation.y -= 90.f * event.dt;
  if(inputManager.IsKeyPressed(GLFW_KEY_D))
    m_cube.rotation.y += 90.f * event.dt;
*/
	m_cube.rotation.x += 90.f * event.dt;
	m_cube.rotation.y += 45.f * event.dt;
	s_time += event.dt;
	if (s_time > 5.f)
	{
		updateTextureIndex();
	}
}

void AppLayer::OnMousePress([[maybe_unused]] const MouseButtonPressedEvent& event)
{
	updateTextureIndex();
}

AppLayer::AppLayer()
	: m_textures{},
	m_shader{
		"res/shaders/basic_vertex.vert",
		"res/shaders/basic_fragment.frag"
	},
	m_currentTextureIndex{0},
	m_remainTimeToChangeTexture{0}
{
	m_textures.reserve(5);
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

	std::vector<std::filesystem::path> pathTextures;
	xengine_prod_assertmsg(
		std::filesystem::exists("res/images")
		&& std::filesystem::is_directory("res/images"),
		"res/images is not exist or res/images not directory"
	);

	for (const auto& entry : std::filesystem::directory_iterator{"res/images"})
	{
		if (entry.is_regular_file())
			pathTextures.emplace_back(entry);
	}

	xengine_prod_assertmsg(pathTextures.size() != 0, "Could find any files in directory res/images")

	for (const auto& path : pathTextures)
		m_textures.emplace_back(path.string(), GL_TEXTURE_2D);

  m_vao.Bind();
  m_vbo.SetData(vertices, sizeof(vertices), GL_STATIC_DRAW);
  m_vbo.SetAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  m_vbo.SetAttribute(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, uvPos));
  m_vao.Unbind();
  m_cube.position = glm::vec3(0.f,0.f,-3.f);
  m_camera.SetFov(45.f);
}