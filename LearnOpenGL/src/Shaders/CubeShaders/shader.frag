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

struct Light
{
    vec3 position;
    vec3 direction;
    float innerCutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Light light;

void main()
{
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));

    vec3 norm = normalize(normal);

    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoords));

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoords));

    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + 
    		                    light.quadratic * (distance * distance)); 
    
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.innerCutOff - light.outerCutOff;
    float intensitity = clamp((theta - light.outerCutOff)/epsilon, 0.0, 1.0);

    fragColor = vec4(attenuation * intensitity * ( ambient + diffuse + specular ), 1.0f);
} 