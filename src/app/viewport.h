// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <glad/glad.h>

struct ViewportSettings {
    float width;
    float height;
    GLuint texture_id;
};

class Viewport {
public:
    explicit Viewport(const ViewportSettings& settings);

    auto Draw() const -> void;

private:
    static constexpr float kTopOffset = 18.0f;

    ViewportSettings settings_;
};