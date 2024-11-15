#version 140
#extension GL_ARB_compatibility: enable
in vec3 pos;
in vec2 textureCoord;

out vec2 uv;
out vec4 color;

uniform mat4 Mvp;

void main() 
{
   gl_Position = Mvp * vec4(pos, 1.0); 
   color = gl_Color;   
   uv = textureCoord;
}


