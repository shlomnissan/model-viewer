# Copyright 2024 Betamark Pty Ltd. All rights reserved.
# Author: Shlomi Nissan (shlomi@betamark.com)

cmake_minimum_required(VERSION 3.22.1)

project(model-viewer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(${CMAKE_SOURCE_DIR}/cmake)

include(cmake/ShaderString.cmake)
ShaderString()

find_package(fmt REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(imgui REQUIRED)

set(CORE_SOURCES
    src/core/camera.cpp
    src/core/camera.h
    src/core/framebuffer.cpp
    src/core/framebuffer.h
    src/core/mesh.cpp
    src/core/mesh.h
    src/core/shader.cpp
    src/core/shader.h
    src/core/window.cpp
    src/core/window.h
)

set(LIBS_SOURCES
    libs/glad/glad.c
    libs/imgui/imgui_impl_glfw.cpp
    libs/imgui/imgui_impl_glfw.h
    libs/imgui/imgui_impl_opengl3.cpp
    libs/imgui/imgui_impl_opengl3.h
)

set(APP_SOURCES
    src/app/menu.cpp
    src/app/menu.h
    src/app/viewport.cpp
    src/app/viewport.h
    src/main.cpp
)

add_executable(model-viewer ${LIBS_SOURCES} ${CORE_SOURCES} ${APP_SOURCES})

target_include_directories(model-viewer PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/libs
)

target_link_libraries(
    model-viewer PRIVATE
      fmt::fmt
      glfw
      glm::glm
      OpenGL::GL
      imgui::imgui
)