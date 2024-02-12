// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "menu.h"

#include <imgui.h>
#include <fmt/format.h>


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

auto Menu::ShowAbout() -> void {
    // TODO: #
}

auto Menu::ShowFileSelection() -> void {
    // TODO: #
}