#version 130
precision highp float;
precision lowp int;

in vec3 aVertexPosition;

uniform mat4 uModelViewProjectionMatrix = mat4(1.0);

smooth out vec3 WorldSpacePosition;

invariant gl_Position;

void main()
{
    WorldSpacePosition = aVertexPosition;

    gl_Position = uModelViewProjectionMatrix * vec4(aVertexPosition, 1.0);
}
