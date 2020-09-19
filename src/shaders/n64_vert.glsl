#version 330 core
layout(location = 0) in vec3 in_position;
layout(location = 2) in vec2 in_texture;
uniform mat4 ctm;
uniform mat4 projection;
uniform mat4 modelView;
out vec2 texcoord;
out float logz;

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

	int far = 1000;
	int near = 1;
	float C = 0.01;

	float FC = 1.0/log(far*C + 1);

  	gl_Position = projection * modelView * ctm * tmp_pos / tmp_pos.w;
	logz = log(gl_Position.w*C + 1)*FC;
	gl_Position.z = (2*logz - 1)*gl_Position.w;
}