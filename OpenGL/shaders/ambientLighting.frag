#version 330 core

in vec2 texCord;

out vec4 color;
  
uniform sampler2D tex;
uniform vec3 lightColor;

void main()
{
    float ambientStrength = 0.1f;
    vec3 ambient = lightColor * ambientStrength;

    color = texture(tex,texCord) * vec4(ambient, 1.0f);	
}