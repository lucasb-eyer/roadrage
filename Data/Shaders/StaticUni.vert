#version 130
precision highp float;
precision lowp int;

in vec3 aVertexPosition;

uniform mat4 uModelViewProjectionMatrix = mat4(1.0);

invariant gl_Position;

void main()
{
    gl_Position = uModelViewProjectionMatrix * vec4(aVertexPosition, 1.0);
//     gl_Position = vec4(0.5, 0.5, 0.0, 1.0);
}
