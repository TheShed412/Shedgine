#version 300 es
layout(location = 0) in mediump vec3 in_position;
layout(location = 1) in mediump vec4 in_color;
uniform mediump mat4 ctm;
uniform mediump mat4 projection;
out mediump vec4 color;
 
void main()
{
  color = in_color;
  vec4 tmp_pos = vec4(in_position, 1);
  gl_Position = projection * ctm * tmp_pos / tmp_pos.w;
}