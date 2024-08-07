// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <deque>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "app/grid.h"
#include "app/menu.h"
#include "app/viewport.h"

#include "core/camera.h"
#include "core/framebuffer.h"
#include "core/mesh.h"
#include "core/model.h"
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

    auto models = std::deque<Model> {};
    menu.OnLoad([&models](std::string_view file) {
        models.emplace_back(file);
        if (models.size() > 1) models.pop_front();
    });

    auto monkey = Mesh {monkey_vertex_0, monkey_index_0};
    auto material_color = glm::vec3 {0.6f, 0.6f, 0.6f};

    window.Start([&]([[maybe_unused]] const double delta){
        framebuffer.Bind();
        glClearColor(0.96f, 0.94f, 0.93f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Update(window);
        grid.Draw(camera);

        auto model = glm::mat4{1.0f};
        if (models.empty()) {
            model = glm::translate(model, {0.0f, 0.5f, 0.0f});
        }

        shader.SetUniform("Projection", camera.Projection());
        shader.SetUniform("ModelView", camera.View() * model);
        shader.SetUniform("NormalMatrix", glm::mat3(glm::inverse(glm::transpose(camera.View() * model))));
        shader.SetUniform("Light.Position", glm::vec3{0.0f});
        shader.SetUniform("Light.La", glm::vec3{0.5f});
        shader.SetUniform("Light.Ld", glm::vec3{0.8f});
        shader.SetUniform("Material.Ka", material_color);
        shader.SetUniform("Material.Kd", material_color);

        if (models.empty()) monkey.Draw(shader);
        for (const auto& model : models) {
            model.Draw(shader);
        }

        framebuffer.Unbind();

        menu.Draw();
        viewport.Draw();
    });

    return 0;
}