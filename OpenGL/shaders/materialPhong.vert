#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 tCord;
layout(location = 2) in vec3 normal;

out vec3 FragPos;
out vec3 Normals;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection; 

void main()
{
	gl_Position = projection * view * model * vec4(position.x,position.y,position.z, 1.0f);
	Normals = mat3(transpose(inverse(model))) * normal; 
	FragPos = vec3(model * vec4(position,1.0f));
}