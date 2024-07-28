// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "camera.h"

#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

Camera::Camera(float fov, float width, float height) {
    projection_ = glm::perspective(fov, width / height, 0.1f, 1000.0f);
}

auto Camera::Projection() const -> glm::mat4 {
    return projection_;
}

auto Camera::View() const -> glm::mat4 {
    return glm::lookAt(position_, target_, up_);
}

auto Camera::Update(Window& window) -> void {
    auto control_key = window.GetKey(GLFW_KEY_LEFT_ALT, GLFW_PRESS);
    if (control_key) {
        auto curr_pos = window.mouse_pos();

        if (first_pos_) {
            first_pos_ = false;
            last_pos_ = curr_pos;
        }

        auto offset_pos = MousePosition {
            curr_pos.first - last_pos_.first,
            last_pos_.second - curr_pos.second
        };

        if (window.GetMouseButton(GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS)) {
            Zoom(offset_pos);
        }
        if (window.GetMouseButton(GLFW_MOUSE_BUTTON_MIDDLE, GLFW_PRESS)) {
            Pan(offset_pos);
        }
        if (window.GetMouseButton(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS)) {
            Rotate(offset_pos);
        }

        last_pos_ = curr_pos;
    }

    const auto pos_x = distance_ * sin(yaw_) * cos(pitch_);
    const auto pos_y = distance_ * sin(pitch_);
    const auto pos_z = distance_ * cos(yaw_) * cos(pitch_);
    position_ = target_ + glm::vec3(pos_x, pos_y, pos_z);
}

auto Camera::Zoom(const MousePosition& offset_pos) -> void {
    distance_ += offset_pos.first * -0.01f;
    distance_ = std::max(0.1f, distance_);
}

auto Camera::Pan(const MousePosition& offset_pos) -> void {
    const auto direction = glm::normalize(target_ - position_);
    const auto right = glm::normalize(glm::cross(direction, {0.0f, 1.0f, 0.0f}));
    const auto up = glm::cross(right, direction);

    const auto pan_h = right * offset_pos.first * SPEED;
    const auto pan_v = up * offset_pos.second * SPEED;
    target_ -= pan_h + pan_v;
}

auto Camera::Rotate(const MousePosition& offset_pos) -> void {
    yaw_ += offset_pos.first * -SPEED;
    pitch_ += offset_pos.second * -SPEED;

    const auto pitch_limit = glm::half_pi<float>() - glm::epsilon<float>();
    pitch_ = std::clamp(pitch_, -pitch_limit, pitch_limit);
}