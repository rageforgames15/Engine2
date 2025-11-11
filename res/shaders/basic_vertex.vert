#version 460 core

layout(location = 0) in vec3 in_Positions;
layout(location = 1) in vec2 in_UVPos;

uniform mat4 u_modelMat;
uniform mat4 u_viewMat;
uniform mat4 u_projMat;

out vec2 o_UVPos;

void main()
{
  gl_Position = u_projMat * u_viewMat * u_modelMat * vec4(in_Positions, 1.0f);
  o_UVPos = in_UVPos;
}
