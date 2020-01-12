#version 300 es
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
uniform mat4 ctm;
out vec4 color;
 
void main()
{
  color = in_color;
  vec4 tmp_pos = vec4(in_position, 1);
  gl_Position = ctm * tmp_pos;
}