#version 330 core
out vec4 FragColor;

in vec4 vertexColor;
in vec2 texCoord;

uniform sampler2D texSampler1;
uniform sampler2D texSampler2;

void main()
{
    FragColor = mix(texture(texSampler1, texCoord), texture(texSampler2, texCoord), 0.2);
} 