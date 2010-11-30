#version 130
precision highp float;
precision lowp int;

smooth in vec3 WorldSpacePosition;

uniform vec3 uMax = vec3(100.0);

out vec4 oColor;

void main ()
{
    vec3 cpos = clamp(WorldSpacePosition/uMax, vec3(-1.0), vec3(1.0));
    vec3 direction = normalize(abs(WorldSpacePosition));

    oColor = vec4(direction - (cpos + vec3(1.0)) * 0.5, 1.0);
}
