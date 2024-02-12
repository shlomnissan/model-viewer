// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "grid.h"

#include <fmt/printf.h>

#define BUFFER_OFFSET(offset) ((void*)(offset * sizeof(GLfloat)))
#define STRIDE(stride) (sizeof(GLfloat) * stride)

Grid::Grid(unsigned int dimensions) : dimensions_(dimensions) {
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    ConfigureVertices();    

    // clean-up
    glBindVertexArray(0);
    glDeleteBuffers(1, &vbo_);
}

auto Grid::ConfigureVertices() -> void {
    auto vertex_data = std::vector<float>{};

    auto div = static_cast<float>(dimensions_) / 2;

    auto x = -div;
    for (auto i = 0; i <= dimensions_; ++i) {
        int color = (x == 0) ? 0x0000FF : 0x383838;
        AddPoint({x, -0.0f, -div}, vertex_data, color);
        AddPoint({x, -0.0f, div}, vertex_data, color);
        x += 1.0f;
    }

    auto z = -div;
    for (auto i = 0; i <= dimensions_; ++i) {
        int color = (z == 0) ? 0xFF0000 : 0x383838;
        AddPoint({-div, -0.0f, z}, vertex_data, color);
        AddPoint({div, -0.0f, z}, vertex_data, color);
        z += 1.0f;
    }

    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertex_data.size() * sizeof(float),
        vertex_data.data(),
        GL_STATIC_DRAW
    );

    // vertices
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE(6), BUFFER_OFFSET(0));

    // colors
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, STRIDE(6), BUFFER_OFFSET(3));
}

auto Grid::AddPoint(
    const std::vector<float>& position,
    std::vector<float>& container,
    int color
) -> void {
    container.insert(container.end(), position.begin(), position.end());
    auto color_vec = std::vector<float> {
        ((color >> 16) & 0xFF) / 255.0f,
        ((color >> 8) & 0xFF) / 255.0f,
        ((color) & 0xFF) / 255.0f,
    };
    container.insert(container.end(), color_vec.begin(), color_vec.end());
}

auto Grid::Draw(const Camera& camera) const -> void {
    shader_.Use();
    shader_.SetMat4("Projection", camera.Projection());
    shader_.SetMat4("View", camera.View());
    glBindVertexArray(vao_);
    glDrawArrays(GL_LINES, 0, dimensions_ * 6);
}