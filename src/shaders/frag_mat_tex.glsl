#version 300 es
out mediump vec4 FragColor;
 
uniform mediump vec3 position; 
uniform mediump vec3 ambient;
uniform mediump vec3 diffuse;
uniform mediump vec3 specular;
uniform mediump float constant;
uniform mediump float linear;
uniform mediump float quadratic;

 
in mediump vec3 FragPos;  
in mediump vec3 Normal;
// Data read from Mtl
//Material
in mediump vec4 Ambient;
in mediump vec4 Diffuse;
in mediump vec4 Specular;
in mediump float shininess;
in mediump float logz;
 
uniform mediump vec3 viewPos;// should be camera pos
 
void main()
{
	// ambient
    mediump vec3 ambient = Ambient.xyz * Diffuse.rgb;
  	
    // diffuse 
    mediump vec3 norm = normalize(Normal);
    mediump vec3 lightDir = normalize(position - FragPos);
    mediump float diff = max(dot(norm, lightDir), 0.0);
    mediump vec3 diffuse = diffuse * diff * Diffuse.rgb;
      
    // attenuation
    mediump float distance = length(position - FragPos);
    mediump float attenuation = 1.0 / (constant + (linear * distance) + (quadratic * (distance * distance)));    
	// specular
    mediump vec3 viewDir = normalize(position - FragPos);
    mediump vec3 reflectDir = reflect(-lightDir, norm);  
    mediump float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    mediump vec3 specular = specular * spec * Specular.rgb;

    diffuse *= attenuation;
    specular *= attenuation;
	  
    mediump vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
    gl_FragDepth = logz;
}