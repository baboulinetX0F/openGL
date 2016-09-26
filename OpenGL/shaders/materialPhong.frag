#version 330 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 texCord;
in vec3 Normals;
in vec3 FragPos;

out vec4 color;
 
uniform Material material; 
uniform Light light;
uniform vec3 viewPos;

void main()
{
    float ambientStrength = 0.1f;    

    vec3 ambient = light.ambient * material.ambient;    

    vec3 norm = normalize(Normals);
    vec3 lightDir = normalize(light.position - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    float spec = pow(max(dot(norm,reflectDir),0.0), material.shininess);
    vec3 specular = spec * material.specular * light.specular;

    vec3 result = (ambient + diffuse + specular);
    color = vec4(result, 1.0f);
}