#version 460 core
#pragma debug(on)
#pragma optimize(off)

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;

struct LightInfo {
    vec3 Position;
    vec3 La;
    vec3 Ld;
};

struct MaterialInfo {
    vec3 Ka;
    vec3 Kd;
};

out vec3 color;

uniform mat4 Projection;
uniform mat4 ModelView;
uniform mat3 NormalMatrix;
uniform LightInfo Light;
uniform MaterialInfo Material;

void SetViewSpace(out vec4 position, out vec3 normal) {
    position = ModelView * vec4(aPosition, 1.0);
    normal = normalize(NormalMatrix * aNormal);
}

vec3 LightReflection(const in vec4 position, const in vec3 normal) {
    vec3 s = normalize(Light.Position - vec3(position));
    vec3 r = reflect(-s, normal);

    vec3 ambient = Light.La * Material.Ka;
    vec3 diffuse = Light.Ld * Material.Kd *  max(dot(s, normal), 0);

    return ambient + diffuse;
}

void main() {
    vec4 position;
    vec3 normal;

    SetViewSpace(position, normal);

    color = LightReflection(position, normal);
    gl_Position = Projection * position;
}