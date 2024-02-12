#version 460 core
#pragma debug(on)
#pragma optimize(off)

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;

out vec3 color;

uniform mat4 Projection;
uniform mat4 View;

void main() {
    gl_Position = Projection * View * vec4(aPosition, 1.0);

    color = aColor;
}