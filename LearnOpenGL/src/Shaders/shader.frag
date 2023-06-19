#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

float near = 0.1; 
float far  = 100.0; 
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (1/(depth*(1/far+1/near)+1/near)-near)/(far-near);
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{             
    float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
    depth = LinearizeDepth(gl_FragCoord.z);
    FragColor = vec4(vec3(depth), 1.0);
}

//void main()
//{    
//    FragColor = texture(texture_diffuse1, TexCoords);
//    FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
//}