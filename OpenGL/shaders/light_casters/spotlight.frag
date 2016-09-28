#version 330 core

struct Material
{    
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 direction;
    float cutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec2 TexCord;
in vec3 Normals;
in vec3 FragPos;

out vec4 color;
 
uniform Material material; 
uniform Light light;
uniform vec3 viewPos;

void main()
{
    vec3 lightDir = normalize(light.position - FragPos);
    float theta = dot(lightDir, normalize(-light.direction));

    if (theta > light.cutOff)
    {

    vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCord));    

    vec3 norm = normalize(Normals);
    
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,TexCord));

    float spec = pow(max(dot(norm,reflectDir),0.0), material.shininess);
    vec3 specular = spec * vec3(texture(material.specular,TexCord)) * light.specular;

    float distance    = length(light.position - FragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 

    vec3 emission = vec3(texture(material.emission,TexCord));
   
    diffuse  *= attenuation;
    specular *= attenuation;
  
    vec3 result = (ambient + diffuse + specular + emission);
    color = vec4(result, 1.0f);
    }
    else
    {
        color = vec4(light.ambient * vec3(texture(material.diffuse, TexCord)), 1.0f);
    }
}