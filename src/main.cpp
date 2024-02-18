// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "app/grid.h"
#include "app/menu.h"
#include "app/viewport.h"

#include "core/camera.h"
#include "core/framebuffer.h"
#include "core/mesh.h"
#include "core/shader.h"
#include "core/window.h"

#include "mesh/cube.h"

#include "shaders/headers/scene_vert.h"
#include "shaders/headers/scene_frag.h"

auto main() -> int {
    const auto width = 1024;
    const auto height = 768;

    auto window = Window {width, height, "Model Viewer"};
    auto camera = Camera{45.0f, width, height};
    auto grid = Grid{24};

    auto shader = Shader {{
        {ShaderType::kVertexShader, _SHADER_scene_vert},
        {ShaderType::kFragmentShader, _SHADER_scene_frag}
    }};

    glEnable(GL_DEPTH_TEST);

    auto framebuffer = Framebuffer {width, height};
    auto menu = Menu {};
    auto viewport = Viewport {{
        .width = static_cast<float>(width),
        .height = static_cast<float>(height),
        .texture_id = framebuffer.texture_id()
    }};

    auto cube = Mesh {cube_vertex_0, cube_index_0};
    auto light_position = glm::vec3 {0.0f, 10.0f, 5.0f};
    auto material_color = glm::vec3 {1.0f, 0.5f, 0.31f};

    window.Start([&]([[maybe_unused]] const double delta){
        framebuffer.Bind();
        glClearColor(0.17f, 0.16f, 0.29f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Update(window);
        grid.Draw(camera);

        auto model = glm::mat4{1.0f};
        model = glm::translate(model, {0.0f, 0.5f, 0.0f});

        shader.SetMat4("Projection", camera.Projection());
        shader.SetMat4("ModelView", camera.View() * model);
        shader.SetVec3("LightSource.position", glm::vec3(camera.View() * glm::vec4(light_position, 1.0)));
        shader.SetVec3("LightSource.ambient", glm::vec3{0.2f});
        shader.SetVec3("LightSource.diffuse", glm::vec3{1.0f});
        shader.SetVec3("SurfaceMaterial.ambient", material_color);
        shader.SetVec3("SurfaceMaterial.diffuse", material_color);

        cube.Draw(shader);
        framebuffer.Unbind();

        menu.Draw();
        viewport.Draw();
    });

    return 0;
}