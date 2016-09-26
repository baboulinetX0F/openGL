#version 330 core

in vec2 texCord;
in vec3 Normals;
in vec3 FragPos;

out vec4 color;
  
uniform sampler2D tex;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    float ambientStrength = 0.1f;
    float specularStrength = 0.5f;

    vec3 ambient = lightColor * ambientStrength;

    vec3 norm = normalize(Normals);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = lightColor * diff;

    float spec = pow(max(dot(norm,reflectDir),0.0),32);
    vec3 specular = spec * specularStrength * lightColor;

    vec3 result = (ambient + diffuse + specular);
    color = texture(tex,texCord) * vec4(result, 1.0f);
}