#pragma once
#include "Layer.h"
#include "Events/Events.h"
#include "Events/ApplicationEvents.h"
#include "Events/InputEvents.h"
#include "Events/MouseEvents.h"
#include "OpenGL/OpenGLBuffers.h"
#include "OpenGL/OpenGLShader.h"
#include "OpenGL/OpenGLTexture.h"
#include "Transform.h"
#include "Camera.h"
#include <vector>

class AppLayer
  : public Layer
{
public:
  virtual void OnEvent(Event& event) override;
  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void Draw(const DrawData&) override;

  void OnTick(const ApplcationTickEvent& ev);
  void OnMousePress(const MouseButtonPressedEvent& ev);
  AppLayer();
private:
	void updateTextureIndex();
private:
	std::vector<OpenGLTexture> m_textures;
  OpenGLShader m_shader;
  OpenGLVAO m_vao;
  OpenGLVBO m_vbo;
  Transform m_cube;
  Camera m_camera;
	size_t m_currentTextureIndex;
	double m_remainTimeToChangeTexture;
};
