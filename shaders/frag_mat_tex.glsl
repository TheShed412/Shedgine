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
 
uniform vec3 viewPos;// should be camera pos
 
uniform float shininess; // Ns in mtl file
 
void main()
{    
    // Light light2;
    // light2.position = vec3(0,1,0);
    // light2.ambient = vec3(1.0, 1.0, 1.0);
    // light2.diffuse = vec3(1.0, 1.0, 1.0);
    // light2.specular = vec3(1.0, 1.0, 1.0);
    // float constant = 1.0;
    // float linear = 0.01;
    // float quadratic = 0.01;
    //light2 = light;
	// ambient
    vec3 ambient = ambient * Diffuse.rgb;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffuse * diff * Diffuse.rgb;
      
    // attenuation
    float distance = length(position - FragPos);
    float attenuation = 1.0 / (constant + (linear * distance) + (quadratic * (distance * distance)));    
	// specular
    vec3 viewDir = normalize(vec3(0.0,4.0,10.0) - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 94.117647);
    vec3 specular = specular * spec * Specular.rgb;
	  
    vec3 result = ambient + (attenuation * (diffuse + specular));
    FragColor = vec4(result, 1.0);
}