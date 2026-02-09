

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

float aspect = 1;

uniform vec3 Offset;
out vec3 ourColor;

void main()
{
    gl_Position = vec4((((aPos.x*aspect)*cos(Offset.x))-(aPos.y*sin(Offset.x)))/aspect,((aPos.x*aspect)*sin(Offset.x))+(aPos.y*cos(Offset.x)),aPos.z, 1.0);
    ourColor = aColor;
}
