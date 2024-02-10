// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "window.h"

#include <GLFW/glfw3.h>
#include <fmt/format.h>
#include <imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

constexpr auto callback_error =
[](int error, const char* message) {
    fmt::print("Error ({}): {}\n", error, message);
};

constexpr auto callback_resize =
[](GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    auto instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (instance->on_resize()) {
        instance->on_resize()(width, height);
    }
};

Window::Window(int width, int height, std::string_view title) {
    glfwSetErrorCallback(callback_error);

    if (!glfwInit()) {
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window_ = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

    if (window_ == nullptr) {
        glfwTerminate();
        return;
    }

     glfwMakeContextCurrent(window_);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        return;
    }

    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window_, callback_resize);
    glfwSetWindowUserPointer(window_, this);

    glViewport(0, 0, width, height);

    InitImgui();
}

auto Window::InitImgui() -> void {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init();
}

auto Window::Start(const std::function<void(const double delta)> &program) -> void {
    auto last_frame = 0.0f;
    while(!glfwWindowShouldClose(window_)) {
        auto time = glfwGetTime();
        auto delta = time - last_frame;
        last_frame = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        program(delta);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}

Window::~Window() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window_);
    glfwTerminate();
}