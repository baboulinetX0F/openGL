#version 330 core

in vec2 texCord;

out vec4 color;
  
uniform sampler2D tex;
uniform vec3 lightColor;

void main()
{
    color = texture(tex,texCord) * vec4(lightColor, 1.0f);	
}