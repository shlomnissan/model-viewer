// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "core/shader.h"
#include "core/camera.h"

#include "shaders/headers/grid_vert.h"
#include "shaders/headers/grid_frag.h"

class Grid {
public:
    Grid(unsigned int dimensions);

    auto Draw(const Camera& camera) const -> void;

private:
    unsigned int dimensions_ {0};
    unsigned int vao_ {0};
    unsigned int vbo_ {0};

    Shader shader_ {{
        {ShaderType::kVertexShader, _SHADER_grid_vert},
        {ShaderType::kFragmentShader, _SHADER_grid_frag}
    }};

    auto AddPoint(
        const std::vector<float>& position,
        std::vector<float>& container,
        int color
    ) -> void;

    auto ConfigureVertices() -> void; 
};