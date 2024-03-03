// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include <assimp/scene.h>

#include "core/mesh.h"
#include "core/shader.h"

class Model {
public:
    explicit Model(std::string_view file);

    auto Draw(const Shader& program) const -> void;

private:
    std::vector<Mesh> mesh_;
    std::string directory_;

    auto GetIndices(const aiMesh* mesh) const -> std::vector<unsigned int>;
    auto GetVertices(const aiMesh* mesh) const -> std::vector<float>;
    auto ProcessNode(const aiNode* node, const aiScene* scene) -> void;
    auto SetDirectory(std::string_view filename) -> void;
};

struct ModelError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};