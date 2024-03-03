// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "model.h"

#include <filesystem>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <fmt/format.h>

Model::Model(std::string_view file) {
    auto importer = Assimp::Importer{};
    auto scene = importer.ReadFile(file.data(), aiProcess_Triangulate | aiProcess_FlipUVs);
    if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        throw ModelError {fmt::format("Failed to load model {}\n", file)};
    }
    SetDirectory(file);
    ProcessNode(scene->mRootNode, scene);
}

auto Model::Draw(const Shader& program) const -> void {
    for (const auto& mesh : mesh_) mesh.Draw(program);
}

auto Model::ProcessNode(const aiNode* node, const aiScene* scene) -> void {
    for (auto i = 0; i < node->mNumMeshes; ++i) {
        auto mesh = scene->mMeshes[node->mMeshes[i]];
        mesh_.emplace_back(GetVertices(mesh), GetIndices(mesh));
    }

    for (auto i = 0; i < node->mNumChildren; ++i) {
        ProcessNode(node->mChildren[i], scene);
    }
}

auto Model::GetVertices(const aiMesh* mesh) const -> std::vector<float> {
    auto output = std::vector<float> {};
    for (auto i = 0; i < mesh->mNumVertices; ++i) {
        // vertices
        output.emplace_back(mesh->mVertices[i].x);
        output.emplace_back(mesh->mVertices[i].y);
        output.emplace_back(mesh->mVertices[i].z);

        // normals
        output.emplace_back(mesh->HasNormals() ? mesh->mNormals[i].x : 0.0f);
        output.emplace_back(mesh->HasNormals() ? mesh->mNormals[i].y : 0.0f);
        output.emplace_back(mesh->HasNormals() ? mesh->mNormals[i].z : 0.0f);

        // texture coordinates
        output.emplace_back(mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][i].x : 0.0f);
        output.emplace_back(mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][i].y : 0.0f);
    }
    return output;
}

auto Model::GetIndices(const aiMesh* mesh) const -> std::vector<unsigned int> {
    auto output = std::vector<unsigned int> {};
    for (auto i = 0; i < mesh->mNumFaces; ++i) {
        auto face = mesh->mFaces[i];
        for (auto j = 0; j < face.mNumIndices; ++j) {
            output.emplace_back(face.mIndices[j]);
        }
    }
    return output;
}

auto Model::SetDirectory(std::string_view file) -> void {
    auto path = std::filesystem::path {file};
    if (path.has_parent_path()) {
        directory_ = path.parent_path().string();
    }
}