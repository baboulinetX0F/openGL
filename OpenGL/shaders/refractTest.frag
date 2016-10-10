#version 330 core

in vec3 Normal;
in vec3 Position;

out vec4 color;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{   
    // ratio between both materials the light passes through.
    // ex. materials : Air 1.00 | Water 1.33 | Ice 1.309 | Glass 1.52 | Diamond 2.42
    float ratio = 1.0/1.52;
    vec3 I = normalize(Position - cameraPos);
    vec3 R = reflect(I, normalize(Normal));
    color = texture(skybox, R);
}