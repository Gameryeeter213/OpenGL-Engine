#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

float aspect = 1.0f;

uniform vec3 Offset;
out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(((((aPos.x*aspect)*cos(Offset.x))-(aPos.y*sin(Offset.x)))/aspect)*2,(((aPos.x*aspect)*sin(Offset.x))+(aPos.y*cos(Offset.x)))*2,aPos.z, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}
