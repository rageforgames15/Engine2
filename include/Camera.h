#pragma once
#include "Transform.h"

class Camera
{
public:
  glm::mat4 GetViewMatrix();
  Transform& GetTransform();

  Camera() = default;
  ~Camera() = default;
private:
  Transform m_transform;
};
