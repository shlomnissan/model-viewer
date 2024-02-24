#version 460 core
#pragma debug(on)
#pragma optimize(off)

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;

out vec4 position;
out vec3 normal;

uniform mat4 Projection;
uniform mat4 ModelView;
uniform mat3 NormalMatrix;

void main() {
    position = ModelView * vec4(aPosition, 1.0);
    normal = normalize(NormalMatrix * aNormal);

    gl_Position = Projection * position;
}