#include "Transform.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <cmath>
#include <glm/ext/quaternion_common.hpp>

static glm::vec3 worldFowardVec = glm::vec3(0,0,-1);
static glm::vec3 worldUpVec = glm::vec3(0,1,0);
static glm::vec3 worldRightVec = glm::vec3(1,0,0);

struct SinAndCosStruct
{
  float cos;
  float sin;
};

SinAndCosStruct CalculateSinAndCos(float x)
{
  SinAndCosStruct val;
  val.cos = cosf(x);
  val.sin = sinf(x);
  return val;
}

glm::quat CalculateQuatRotationFromEuler(const glm::vec3& euler)
{
  SinAndCosStruct xSinCos = CalculateSinAndCos(glm::radians(euler.x) / 2);
  SinAndCosStruct ySinCos = CalculateSinAndCos(glm::radians(euler.y) / 2);
  SinAndCosStruct zSinCos = CalculateSinAndCos(glm::radians(euler.z) / 2);

  glm::quat quat(
    (xSinCos.cos * ySinCos.cos * zSinCos.cos)
    +
    (xSinCos.sin * ySinCos.sin * zSinCos.sin),
    (xSinCos.sin * ySinCos.cos * zSinCos.cos)
    -
    (xSinCos.cos * ySinCos.sin * zSinCos.sin),
    (xSinCos.cos * ySinCos.sin * zSinCos.cos)
    +
    (xSinCos.sin * ySinCos.cos * zSinCos.sin),
    (xSinCos.cos * ySinCos.cos * zSinCos.sin)
    -
    (xSinCos.sin * ySinCos.sin * zSinCos.cos)
  );
  return quat;
}

glm::mat4 Transform::ToMatrix()
{
  glm::mat4 posMat(1.0f);
  posMat = glm::translate(posMat, position);
  glm::mat4 rotMat 
    = glm::mat4_cast(CalculateQuatRotationFromEuler(rotation));

  return posMat * rotMat;
}

glm::vec3 Transform::GetFowardVec()
{
  glm::quat quat = CalculateQuatRotationFromEuler(rotation);
  return quat * worldFowardVec;
}

glm::vec3 Transform::GetRightVec()
{
  glm::quat quat = CalculateQuatRotationFromEuler(rotation);
  return quat * worldRightVec;
}

glm::vec3 Transform::GetUpVec()
{
  glm::quat quat = CalculateQuatRotationFromEuler(rotation);
  return quat * worldUpVec;
}

glm::quat Transform::GetQuatRotation()
{
  return CalculateQuatRotationFromEuler(rotation);
}

