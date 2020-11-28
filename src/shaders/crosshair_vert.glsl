#version 330 core
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
uniform mat4 ctm;
uniform mat4 projection;
out vec4 color;
 
void main()
{
  color = in_color;
  vec4 tmp_pos = vec4(in_position, 1);
  gl_Position = projection * ctm * tmp_pos / tmp_pos.w;
}