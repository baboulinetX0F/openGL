#version 330 core

#define NR_POINT_LIGHTS 4 

struct Material
{    
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct PointLight
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct DirLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 TexCord;
in vec3 Normals;
in vec3 FragPos;

out vec4 color;
 
uniform Material material; 
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform vec3 viewPos;

vec3 calculateDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCord));    
    
    vec3 lightDir = normalize(-light.direction);   
    vec3 reflectDir = reflect(-lightDir, normal);

    float diff = max(dot(normal,lightDir),0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,TexCord));

    float spec = pow(max(dot(normal,reflectDir),0.0), material.shininess);
    vec3 specular = spec * vec3(texture(material.specular,TexCord)) * light.specular;   

    return (ambient + diffuse + specular);   
}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragpos)
{
    vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCord));    

    vec3 lightDir = normalize(light.position - fragpos);
    vec3 reflectDir = reflect(-lightDir, normal);

    float diff = max(dot(normal,lightDir),0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,TexCord));

    float spec = pow(max(dot(normal,reflectDir),0.0), material.shininess);
    vec3 specular = spec * vec3(texture(material.specular,TexCord)) * light.specular;

    float distance    = length(light.position - fragpos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 

    vec3 emission = vec3(texture(material.emission,TexCord));

    ambient  *= attenuation;  
    diffuse  *= attenuation;
    specular *= attenuation;   

    return (ambient + diffuse + specular + emission);    
}

void main()
{
    vec3 result;   

    vec3 norm = normalize(Normals);   
    vec3 viewDir = normalize(viewPos - FragPos);

    result = calculateDirLight(dirLight, norm, viewDir);

    for(int i=0;i<NR_POINT_LIGHTS;i++)
    {
       result += calculatePointLight(pointLights[i], norm, viewDir, FragPos); 
    }   

    color = vec4(result, 1.0f);
}