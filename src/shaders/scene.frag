#version 460 core
#pragma debug(on)
#pragma optimize(off)

layout (location = 0) out vec4 frag_color;

struct LightInfo {
    vec3 Position;
    vec3 La;
    vec3 Ld;
};

struct MaterialInfo {
    vec3 Ka;
    vec3 Kd;
};

in vec4 position;
in vec3 normal;

uniform LightInfo Light;
uniform MaterialInfo Material;

vec3 LightReflection(const in vec4 position, const in vec3 normal) {
    vec3 s = normalize(Light.Position - vec3(position));

    vec3 ambient = Light.La * Material.Ka;
    vec3 diffuse = Light.Ld * Material.Kd *  max(dot(s, normal), 0);

    return ambient + diffuse;
}

void main() {
    frag_color = vec4(LightReflection(position, normal), 1.0);
}