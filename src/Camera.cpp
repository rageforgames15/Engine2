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
  return glm::lookAt(
    m_transform.position,
    m_transform.position + m_transform.GetFowardVec(),
    glm::vec3(0,1,0)
  );
}
