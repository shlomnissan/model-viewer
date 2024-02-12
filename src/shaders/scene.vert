#version 460 core
#pragma debug(on)
#pragma optimize(off)

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;

uniform mat4 Projection;
uniform mat4 ModelView;

void main() {
    gl_Position = Projection * ModelView * vec4(aPosition, 1.0);
}