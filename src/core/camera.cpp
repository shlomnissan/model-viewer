// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(float fov, float width, float height) {
    projection_ = glm::perspective(fov, width / height, 0.1f, 1000.0f);
}

auto Camera::Position() const -> glm::vec3 {
    return world_pos_ * position_;
}

auto Camera::Projection() const -> glm::mat4 {
    return projection_;
}

auto Camera::View() const -> glm::mat4 {
    return  glm::translate(glm::mat4{1.0f}, world_pos_) *
            glm::lookAt(position_, target_, up_);
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

    float pos_x = distance_ * sin(horizontal_angle_) * cos(vertical_angle_);
    float pos_y = distance_ * sin(vertical_angle_);
    float pos_z = distance_ * cos(horizontal_angle_) * cos(vertical_angle_);
    position_ = glm::vec3(pos_x, pos_y, pos_z);
}

auto Camera::Zoom(const MousePosition& offset_pos) -> void {
    distance_ += offset_pos.first * -0.01f;
    distance_ = std::max(0.1f, distance_);
}

auto Camera::Pan(const MousePosition& offset_pos) -> void {
    world_pos_.x += offset_pos.first * 0.009f;
    world_pos_.y += offset_pos.second * 0.009f;
}

auto Camera::Rotate(const MousePosition& offset_pos) -> void {
    horizontal_angle_ += offset_pos.first * -0.009f;
    vertical_angle_ += offset_pos.second * -0.009f;
}