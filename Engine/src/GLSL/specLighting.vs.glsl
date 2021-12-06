

#version 400 core
layout (location = 0) in vec4 aPos;
layout (location = 2) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 world_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

void main()
{
    FragPos = vec3(world_matrix * aPos);
    Normal = mat3(transpose(inverse(world_matrix))) * aNormal;  
    
    gl_Position = proj_matrix * view_matrix * vec4(FragPos, 1.0);
}

