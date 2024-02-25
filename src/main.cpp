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

#include "mesh/monkey.h"

#include "shaders/headers/scene_vert.h"
#include "shaders/headers/scene_frag.h"

auto main() -> int {
    const auto width = 1024;
    const auto height = 768;

    auto window = Window {width, height, "3D Model Viewer"};
    auto camera = Camera{45.0f, width, height};
    auto grid = Grid{24};

    auto shader = Shader {{
        {ShaderType::kVertexShader, _SHADER_scene_vert},
        {ShaderType::kFragmentShader, _SHADER_scene_frag}
    }};

    glEnable(GL_DEPTH_TEST);

    auto framebuffer = Framebuffer {width, height};
    auto menu = Menu {width, height};
    auto viewport = Viewport {{
        .width = width,
        .height = height,
        .texture_id = framebuffer.texture_id()
    }};

    menu.OnLoad([](std::string_view file){
        // TODO: load file
    });

    auto monkey = Mesh {monkey_vertex_0, monkey_index_0};
    auto light_position = glm::vec3 {0.0f, 10.0f, 5.0f};
    auto material_color = glm::vec3 {1.0f, 0.5f, 0.31f};

    window.Start([&]([[maybe_unused]] const double delta){
        framebuffer.Bind();
        glClearColor(0.96f, 0.94f, 0.93f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Update(window);
        grid.Draw(camera);

        auto model = glm::mat4{1.0f};
        model = glm::translate(model, {0.0f, 0.5f, 0.0f});

        shader.SetMat4("Projection", camera.Projection());
        shader.SetMat4("ModelView", camera.View() * model);
        shader.SetMat3("NormalMatrix", glm::mat3(glm::inverse(glm::transpose(camera.View() * model))));
        shader.SetVec3("Light.Position", glm::vec3(camera.View() * glm::vec4(light_position, 1.0)));
        shader.SetVec3("Light.La", glm::vec3{0.2f});
        shader.SetVec3("Light.Ld", glm::vec3{1.0f});
        shader.SetVec3("Material.Ka", material_color);
        shader.SetVec3("Material.Kd", material_color);

        monkey.Draw(shader);
        framebuffer.Unbind();

        menu.Draw();
        viewport.Draw();
    });

    return 0;
}