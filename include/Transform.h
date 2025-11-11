#pragma once
#include "glm/glm.hpp"

struct Transform
{
  glm::vec3 position = glm::vec3(0.0f);
  glm::vec3 rotation = glm::vec3(0.0f); // EULER XYZ, (0-360, more or less allowed)

  glm::mat4 ToMatrix();
  glm::vec3 GetRightVec();
  glm::vec3 GetFowardVec();
  glm::vec3 GetUpVec();

  glm::quat GetQuatRotation();
};
