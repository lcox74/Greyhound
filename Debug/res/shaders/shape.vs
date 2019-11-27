
#version 330 core

layout (location = 0) in vec2 aPos;

uniform vec4 aColor;

out vec4 ourColor; 

void main()
{
    gl_Position = vec4(aPos, 0.0f, 1.0);
    ourColor = aColor; // set ourColor to the input color we got from the vertex data
}       