// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "app/menu.h"
#include "app/viewport.h"

#include "core/framebuffer.h"
#include "core/mesh.h"
#include "core/shader.h"
#include "core/window.h"

#include "shaders/headers/vertex.h"
#include "shaders/headers/fragment.h"

auto main() -> int {
    const auto width = 1024;
    const auto height = 768;

    auto window = Window {width, height, "3D Model Viewer"};

    auto shader = Shader {{
        {ShaderType::kVertexShader, _SHADER_vertex},
        {ShaderType::kFragmentShader, _SHADER_fragment}
    }};
    
    glEnable(GL_DEPTH_TEST);

    auto updateProjection = [&shader](int w, int h) {
        auto ratio = static_cast<float>(w) / static_cast<float>(h);
        shader.SetMat4("Projection", glm::perspective(45.0f, ratio, 0.1f, 100.0f));
    };
    updateProjection(width, height);

    auto framebuffer = Framebuffer {width, height};
    auto menu = Menu {};
    auto viewport = Viewport {{
        .width = static_cast<float>(width),
        .height = static_cast<float>(height),
        .texture_id = framebuffer.texture_id()
    }};

    auto triangle = Mesh({
        -0.5f, -0.5f, -2.0f, 1.0f, 0.0f, 0.0f,
         0.0f,  0.5f, -2.0f, 0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -2.0f, 0.0f, 0.0f, 1.0f,
    });

    window.Start([&]([[maybe_unused]] const double delta){
        framebuffer.Bind();
        glClearColor(0.17f, 0.16f, 0.29f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        triangle.Draw(shader);
        framebuffer.Unbind();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        menu.Render();
        viewport.Render();
    });

    return 0;
}