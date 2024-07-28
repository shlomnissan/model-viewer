// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <glm/glm.hpp>

#include <core/window.h>

using MousePosition = std::pair<float, float>;

class Camera {
public:
    Camera(float fov, float width, float height);

    auto Update(Window& window) -> void;
    auto Projection() const -> glm::mat4;
    auto View() const -> glm::mat4;

private:
    static constexpr float SPEED = 0.009f;

    bool first_pos_ {true};

    float distance_ = 6.0f;
    float yaw_ = -0.4f;
    float pitch_ = 0.15f;

    glm::vec3 position_ {4.5f, 2.0f, distance_};
    glm::vec3 target_ {0.0f, 0.0f, 0.0f};
    glm::mat4 projection_ {0.0f};

    MousePosition last_pos_ {0.0f, 0.0f};

    auto Zoom(const MousePosition& offset_pos) -> void;
    auto Pan(const MousePosition& offset_pos) -> void;
    auto Rotate(const MousePosition& offset_pos) -> void;
};