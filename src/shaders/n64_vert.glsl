#version 300 es
layout(location = 0) in mediump vec3 in_position;
layout(location = 2) in mediump vec2 in_texture;
uniform mediump mat4 ctm;
uniform mediump mat4 projection;
uniform mediump mat4 modelView;
out mediump vec2 texcoord;
out mediump float logz;

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

	mediump float far = 1000.0;
	mediump float C = 0.01;

	mediump float FC = 1.0/log(far*C + 1.0);

  	gl_Position = projection * modelView * ctm * tmp_pos / tmp_pos.w;
	logz = log(gl_Position.w*C + 1.0)*FC;
	gl_Position.z = (2.0*logz - 1.0)*gl_Position.w;
}