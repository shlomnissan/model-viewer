#version 460 core
#pragma debug(on)
#pragma optimize(off)

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
};

out vec3 light_intensity;

uniform mat4 Projection;
uniform mat4 ModelView;
uniform Light LightSource;
uniform Material SurfaceMaterial;

vec3 ambient_component() {
    return LightSource.ambient * SurfaceMaterial.ambient;
}

vec3 diffuse_component(const in vec3 position) {
    const mat3 normal_matrix = mat3(inverse(transpose(ModelView)));
    const vec3 normal = normalize(normal_matrix * aNormal);
    const vec3 light_dir = normalize(LightSource.position - vec3(position));
    const float diffuse = max(dot(light_dir, normal), 0);
    return LightSource.diffuse * SurfaceMaterial.diffuse * diffuse;
}

void main() {
    vec4 position = ModelView * vec4(aPosition, 1.0);

    light_intensity = ambient_component() +
                      diffuse_component(vec3(position));

    gl_Position = Projection * position;
}