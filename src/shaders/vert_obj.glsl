#version 300 es
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec2 aTexCoords;
uniform mat4 ctm;
uniform mat4 projection;
uniform mat4 modelView;
out vec2 TexCoords;
 
void main()
{
  TexCoords = aTexCoords;
  vec4 tmp_pos = vec4(in_position, 1);
  gl_Position = projection * modelView * ctm * tmp_pos / tmp_pos.w;
}