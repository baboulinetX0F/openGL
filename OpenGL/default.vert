#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 tCord;

out vec2 texCord;

uniform mat4 transform; 

void main()
{
	gl_Position = transform * vec4(position.x,position.y,position.z, 1.0f);
	texCord = tCord;
}