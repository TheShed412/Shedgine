#version 300 es
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec2 in_texture;
uniform mat4 ctm;
uniform mat4 projection;
uniform mat4 modelView;
out vec4 color;
out vec2 texcoord;
 
void main()
{
  texcoord = in_texture;
  color = in_color;
  vec4 tmp_pos = vec4(in_position, 1);
  gl_Position = projection * modelView * ctm * tmp_pos / tmp_pos.w;
}