#version 460 core

layout(location = 0) in vec3 in_Positions;

void main()
{
  gl_Position = vec4(in_Positions, 1.0f);
}
