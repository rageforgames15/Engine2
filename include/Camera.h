#pragma once
#include "Transform.h"

class Camera
{
public:
  glm::mat4 GetViewMatrix();
  Transform& GetTransform();

  float GetFov() const;
  void SetFov(float fov);

  Camera() = default;
  ~Camera() = default;
private:
  Transform m_transform;
  float m_fov = 45.f;
};
