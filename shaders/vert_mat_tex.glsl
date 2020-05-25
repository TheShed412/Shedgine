#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
 
uniform Mat{
	vec4 aAmbient;
	vec4 aDiffuse;
	vec4 aSpecular;
};
out vec3 FragPos;
out vec3 Normal;
 
out vec4 Ambient;
out vec4 Diffuse;
out vec4 Specular;
 
uniform mat4 ctm;
uniform mat4 modelView;
uniform mat4 projection;
 
void main()
{
	vec3 position = vec3(0,10,0);
    FragPos = vec3( modelView * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(modelView * ctm))) * aNormal;  
	Ambient = aAmbient;
	Diffuse = aDiffuse;
	Specular = aSpecular;
 
	
    vec4 tmp_pos = vec4(aPos, 1);
  	gl_Position = projection * modelView * ctm * tmp_pos / tmp_pos.w;
}