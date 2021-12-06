

#version 400 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
  
uniform vec3 vLightPos; 
uniform vec3 vViewPos; 
uniform vec3 vColor;

void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(vLightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(vViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * vColor;  
        
    vec3 result = (ambient + diffuse + specular) * vec3(1.0f,0.5f,0.31f);
    FragColor = vec4(result, 1.0);
} 

