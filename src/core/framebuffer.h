// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <stdexcept>

#include <glad/glad.h>

class Framebuffer {
public:
    Framebuffer(int width, int height);

    auto Bind() -> void;
    auto Unbind() -> void;

    auto width() { return width_; }
    auto height() { return height_; }
    auto texture_id() { return texture_id_; }

    ~Framebuffer();

private:
    GLuint width_;
    GLuint height_;
    GLuint framebuffer_id_;
    GLuint texture_id_;
};

struct FramebufferError : std::runtime_error {
    using std::runtime_error::runtime_error;
};