// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "viewport.h"

#include <imgui.h>

Viewport::Viewport(const ViewportSettings& settings) : settings_(settings) {}

auto Viewport::Draw() const -> void {
   ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));
    ImGui::Begin("Viewport", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove
    );
    ImGui::SetWindowPos({0, kTopOffset});
    ImGui::SetWindowSize({settings_.width, settings_.height});
    ImGui::GetWindowDrawList()->AddImage(
        (void *)settings_.texture_id,
        ImVec2(0, 0),
        ImVec2(settings_.width, settings_.height),
        ImVec2(0, 1), ImVec2(1, 0)
    );
    ImGui::End();
    ImGui::PopStyleVar();
}