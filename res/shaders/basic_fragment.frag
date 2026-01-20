#version 460 core

uniform sampler2D u_tex;

in vec2 o_UVPos;

out vec4 out_color;

void main()
{
  out_color = texture(u_tex, o_UVPos);
}
