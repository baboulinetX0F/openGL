#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in mat4 instanceModel;

out vec2 TexCord;
out vec3 Normals;
out vec3 FragPos;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * instanceModel * vec4(position, 1.0f);
    TexCord = texCoords;
    Normals = normal;
    FragPos = vec3(instanceModel * vec4(position,1.0f));
}

