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

    auto GetKey(int key, int action) const -> bool;
    auto GetMouseButton(int key, int action) const -> bool;
    auto Resize(const ResizeCallback& callback) { on_resize_ = callback; }
    auto SetMousePosition(double x, double y) -> void;
    auto Start(const TickCallback& program) -> void;

    auto on_resize() { return on_resize_; }
    auto mouse_pos() const { return mouse_pos_; }

    ~Window();

private:
    std::pair<float, float> mouse_pos_ {0.0, 0.0};

    GLFWwindow* window_ {nullptr};
    ResizeCallback on_resize_;

    auto InitImgui() -> void;
};