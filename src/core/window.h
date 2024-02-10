// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <functional>
#include <string_view>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using TickCallback = std::function<void(const double delta)>;
using ResizeCallback = std::function<void(const int, const int)>;

class Window {
public:
    Window(int width, int height, std::string_view title);

    auto Start(const TickCallback& program) -> void;
    auto Resize(const ResizeCallback& callback) { on_resize_ = callback; }

    auto on_resize() { return on_resize_; }

    ~Window();

private:
    GLFWwindow* window_ {nullptr};
    ResizeCallback on_resize_;

    auto InitImgui() -> void;
};