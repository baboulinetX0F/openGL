#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D screenTexture;

const float offset = 1.0 / 300;  

void main()
{
    if (gl_FragCoord.x < 640)
    {
        color = texture(screenTexture, TexCoords) * vec4(1.0f,1.0f,2.0f,1.0f);
    }
    else
    {
        color = texture(screenTexture, TexCoords) * vec4(2.0f,1.0f,1.0f,1.0f);
    }
}  