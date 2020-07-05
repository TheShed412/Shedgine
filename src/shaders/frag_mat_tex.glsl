#version 330 core
out vec4 FragColor;
 
uniform vec3 position; 
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform float constant;
uniform float linear;
uniform float quadratic;

 
in vec3 FragPos;  
in vec3 Normal;
// Data read from Mtl
//Material
in vec4 Ambient;
in vec4 Diffuse;
in vec4 Specular;
in float shininess;
 
uniform vec3 viewPos;// should be camera pos
 
void main()
{
	// ambient
    vec3 ambient = Ambient.xyz * Diffuse.rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffuse * diff * Diffuse.rgb;
      
    // attenuation
    float distance = length(position - FragPos);
    float attenuation = 1.0 / (constant + (linear * distance) + (quadratic * (distance * distance)));    
	// specular
    vec3 viewDir = normalize(position - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specular * spec * Specular.rgb;

    diffuse *= attenuation;
    specular *= attenuation;
	  
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}