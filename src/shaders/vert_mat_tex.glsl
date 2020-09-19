#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
 
uniform MatBlock {
	vec4 aAmbient;
	vec4 aDiffuse;
	vec4 aSpecular;
	float aShine;
} Mat;
out vec3 FragPos;
out vec3 Normal;
 
out vec4 Ambient;
out vec4 Diffuse;
out vec4 Specular;
out float shininess;
out float logz;
 
uniform mat4 ctm;
uniform mat4 modelView;
uniform mat4 projection;
 
void main()
{
    FragPos = vec3(aPos);
	Normal = mat3(transpose(inverse(modelView * ctm))) * aNormal;  
	Ambient = Mat.aAmbient;
	Diffuse = Mat.aDiffuse;
	Specular = Mat.aSpecular;
	shininess = Mat.aShine;
	int far = 1000;
	int near = 1;
	float C = 0.01;

	float FC = 1.0/log(far*C + 1);
	
    vec4 tmp_pos = vec4(aPos, 1);
  	gl_Position = projection * modelView * ctm * tmp_pos / tmp_pos.w;
	logz = log(gl_Position.w*C + 1)*FC;
	gl_Position.z = (2*logz - 1)*gl_Position.w;
}