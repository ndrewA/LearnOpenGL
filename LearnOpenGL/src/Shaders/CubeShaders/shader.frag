#version 330 core

out vec4 fragColor;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoords;

uniform vec3 viewPos;

struct Material
{
    sampler2D   diffuse;
    sampler2D   specular;
    float       shininess;
};

uniform Material material;

struct DirLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirLight dirLight;

struct PointLight
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define MAX_POINT_LIGHTS 4

uniform PointLight pointLights[MAX_POINT_LIGHTS];

struct FlashLight
{
    vec3 position;
    vec3 direction;

    float innerCutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform FlashLight flashLight;

vec3 calcDirLight(DirLight light, vec3 normal, vec3 viewDir) 
{
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0f);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));
    vec3 diffuse = light.diffuse * vec3(texture(material.diffuse, texCoords)) * diff;
    vec3 specular = light.specular * vec3(texture(material.specular, texCoords)) * spec;

    return ambient + diffuse + specular;
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0f);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + 
    		                    light.quadratic * (distance * distance)); 

    vec3 ambient = attenuation * light.ambient * vec3(texture(material.diffuse, texCoords));
    vec3 diffuse = attenuation * light.diffuse * vec3(texture(material.diffuse, texCoords)) * diff;
    vec3 specular = attenuation * light.specular * vec3(texture(material.specular, texCoords)) * spec;

    return ambient + diffuse + specular;
}

vec3 calcFlashLight(FlashLight light, vec3 normal, vec3 fragPos)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0f);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(light.direction, reflectDir), 0.0f), material.shininess);

    float distance      = length(light.position - fragPos);
    float attenuation   = 1.0f / (light.constant + light.linear * distance + 
    		                      light.quadratic * (distance * distance)); 

    float theta     = dot(lightDir, normalize(-light.direction));
    float epsilon   = light.innerCutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);    


    vec3 ambient = attenuation * light.ambient * vec3(texture(material.diffuse, texCoords));
    vec3 diffuse = intensity * attenuation * light.diffuse * vec3(texture(material.diffuse, texCoords)) * diff;
    vec3 specular = intensity * attenuation * light.specular * vec3(texture(material.specular, texCoords)) * spec;

    return ambient + diffuse + specular;
}

void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);

    vec3 result = calcDirLight(dirLight, norm, viewDir);

    for(int i = 0; i < MAX_POINT_LIGHTS; i++)
        result += calcPointLight(pointLights[i], norm, fragPos, viewDir);

    result += calcFlashLight(flashLight, norm, fragPos);

    fragColor = vec4(result, 1.0f);
} 