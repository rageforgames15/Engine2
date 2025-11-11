#include "Camera.h"
#include "Transform.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

Transform& Camera::GetTransform()
{
  return m_transform;
}

glm::mat4 Camera::GetViewMatrix()
{
  // return glm::lookAt(
  //   m_transform.position,
  //   m_transform.position + m_transform.GetFowardVec(),
  //   glm::vec3(0,1,0)
  // );
  glm::mat4 rotationMat
    = glm::mat4_cast(m_transform.GetQuatRotation());
  glm::mat4 posMat
    = glm::translate(glm::mat4(1.0f),  m_transform.position);

  return glm::inverse(posMat * rotationMat);
}

void Camera::SetFov(float fov)
{
  m_fov = fov;
}

float Camera::GetFov() const
{
  return m_fov;
}

