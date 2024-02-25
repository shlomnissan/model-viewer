// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "menu.h"

#include <imgui.h>
#include <portable-file-dialogs.h>

Menu::Menu(const float window_width, const float window_height) :
    window_width_(window_width), window_height_(window_height) {}

auto Menu::Draw() -> void {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            ImGui::MenuItem("Open", nullptr, &show_file_explorer_);
            ImGui::EndMenu();
        }
        ImGui::MenuItem("About", nullptr, &show_about_);
        ImGui::EndMainMenuBar();
    }
    if (show_about_) ShowAbout();
    if (show_file_explorer_) ShowFileSelection();
};

auto Menu::CenteredText(std::string_view text) -> void {
    auto offset = (ImGui::GetWindowWidth() - ImGui::CalcTextSize(text.data()).x) / 2;
    ImGui::SetCursorPosX(offset);
    ImGui::Text(text.data());
}

auto Menu::ShowAbout() -> void {
    const auto width = 300;
    const auto height = 120;

    ImGui::OpenPopup("About ");
    ImGui::SetNextWindowSize({width, height});
    ImGui::SetNextWindowPos({
        (window_width_ - width) / 2,
        (window_height_ - height) / 2
    });

    if (ImGui::BeginPopupModal(
        "About ",
        &show_about_,
        ImGuiWindowFlags_NoResize
    )) {
        ImGui::SetCursorPosY(35);
        CenteredText("3D Model Viewer");
        CenteredText("Version 0.1");
        CenteredText("Copyright Betamark 2014");
        CenteredText("www.betamark.com");
        ImGui::EndPopup();
    }
}

auto Menu::ShowFileSelection() -> void {
    auto selection = pfd::open_file(
        "Select a file", ".",
        {"3D Object File (.obj .dae)", "*.obj", "*.dae"}
    ).result();

    if (!selection.empty()) on_load_(selection[0]);

    show_file_explorer_ = false;
}