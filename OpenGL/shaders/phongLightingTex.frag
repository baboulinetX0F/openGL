#version 330 core

in vec2 texCord;
in vec3 Normals;
in vec3 FragPos;

out vec4 color;
  
uniform sampler2D tex;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
    vec3 objectColor = vec3(1.0f,0.0f,0.0f);
    float ambientStrength = 0.1f;
    vec3 ambient = lightColor * ambientStrength;

    vec3 norm = normalize(Normals);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = lightColor * diff;

    vec3 result = (ambient + diffuse) * objectColor;
    color = vec4(result, 1.0f);
}