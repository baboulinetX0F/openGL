#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 TexCord;
out vec3 Normals;
out vec3 FragPos;

layout (std140) uniform Matrices
{
	mat4 view;
	mat4 projection;
};

uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    TexCord = texCoords;
    Normals = normal;
    FragPos = vec3(model * vec4(position,1.0f));
}