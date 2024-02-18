#version 460 core
#pragma debug(on)
#pragma optimize(off)

layout (location = 0) out vec4 frag_color;

in vec3 light_intensity;

void main() {
    frag_color = vec4(light_intensity, 1.0);
}