#version 300 es
layout(location = 0) in vec3 in_position;
layout(location = 2) in vec2 in_texture;
uniform mat4 ctm;
uniform mat4 projection;
uniform mat4 modelView;
out vec2 texcoord;

uniform MatBlock {
	vec4 aAmbient;
	vec4 aDiffuse;
	vec4 aSpecular;
	float aShine;
} Mat;
 
void main()
{
  texcoord = in_texture;
  vec4 tmp_pos = vec4(in_position, 1);
  gl_Position = projection * modelView * ctm * tmp_pos / tmp_pos.w;
}