#version 300 es
layout (location = 0) in mediump vec3 aPos;
layout (location = 1) in mediump vec3 aNormal;
 
uniform MatBlock {
	vec4 aAmbient;
	vec4 aDiffuse;
	vec4 aSpecular;
	float aShine;
} Mat;
out mediump vec3 FragPos;
out mediump vec3 Normal;
 
out mediump vec4 Ambient;
out mediump vec4 Diffuse;
out mediump vec4 Specular;
out mediump float shininess;
out mediump float logz;
 
uniform mediump mat4 ctm;
uniform mediump mat4 modelView;
uniform mediump mat4 projection;
 
void main()
{
    FragPos = vec3(aPos);
	Normal = mat3(transpose(inverse(modelView * ctm))) * aNormal;  
	Ambient = Mat.aAmbient;
	Diffuse = Mat.aDiffuse;
	Specular = Mat.aSpecular;
	shininess = Mat.aShine;
	mediump float far = 1000.0;
	mediump float C = 0.01;

	mediump float FC = 1.0/log(far*C + 1.0);
	
    mediump vec4 tmp_pos = vec4(aPos, 1.0);
  	gl_Position = projection * modelView * ctm * tmp_pos / tmp_pos.w;
	logz = log(gl_Position.w * C + 1.0) * FC;
	gl_Position.z = (2.0*logz - 1.0)*gl_Position.w;
}