// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

class Menu {
public:
    auto Draw() -> void;

private:
    bool show_about_;
    bool show_file_explorer_;

    auto ShowAbout() -> void;
    auto ShowFileSelection() -> void;
};