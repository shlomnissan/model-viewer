// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <functional>
#include <string_view>

using OnLoadCallback = std::function<void(std::string_view)>;

class Menu {
public:
    Menu(const float window_width, const float window_height);

    auto Draw() -> void;
    auto OnLoad(const OnLoadCallback& callback) { on_load_ = callback; }

private:
    bool show_about_ {false};
    bool show_file_explorer_ {false};
    float window_width_ {0};
    float window_height_ {0};

    OnLoadCallback on_load_;

    auto CenteredText(std::string_view text) -> void;
    auto ShowAbout() -> void;
    auto ShowFileSelection() -> void;
};