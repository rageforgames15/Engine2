#version 460 core

layout(location = 0) in vec3 in_Positions;
layout(location = 1) in vec2 in_UVPos;

uniform mat4 u_mvp;

out vec2 o_UVPos;

void main()
{
  gl_Position = u_mvp * vec4(in_Positions, 1.0f);
  o_UVPos = in_UVPos;
}
