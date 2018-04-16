#version 450 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec4 in_color;

out vec4 v_color;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 transformationMatrix;

void main()
{
    v_color = in_color;
    gl_Position = projectionMatrix * viewMatrix * transformationMatrix * vec4(in_position, 1.0);
}