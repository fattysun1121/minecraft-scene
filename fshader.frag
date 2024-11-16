#version 140
#extension GL_ARB_compatibility: enable

in  vec4 color;
in vec2 uv;

out vec4 FragColor;

uniform sampler2D myTexture;

void main() 
{ 
    FragColor = texture(myTexture, uv);
    
} 
