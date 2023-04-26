#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

out vec4 vertexColor;

void main()
{
    vertexColor = vec4(color, 1.0f);
    gl_Position = vec4(pos, 1.0);
}