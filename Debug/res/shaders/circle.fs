#version 330 core

out vec4 FragColor;  
in vec3 ourColor;
in float radius;

void main()
{
    vec2 pos = mod(gl_FragCoord.xy, vec2(50.0)) - vec2(25.0);
    float dist_squared = dot(pos, pos);

    gl_FragColor = (dist_squared < radius) ? vec4(ourColor, 1.0) : vec4(ourColor, 0.0);
}