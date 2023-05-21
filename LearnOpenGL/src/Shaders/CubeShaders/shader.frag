#version 330 core

out vec4 fragColor;

in vec3 normal;
in vec3 fragPos;

uniform vec3 objectColor;

uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;
    fragColor = vec4(result, 1.0f);
} 