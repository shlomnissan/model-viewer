// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "framebuffer.h"

Framebuffer::Framebuffer(int width, int height) : width_(width), height_(height) {
    glGenFramebuffers(1, &frame_buffer_id_);
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_id_);

    glGenRenderbuffers(1, &render_buffer_id_);
    glBindRenderbuffer(GL_RENDERBUFFER, render_buffer_id_);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, render_buffer_id_);

    glGenTextures(1, &texture_id_);
	glBindTexture(GL_TEXTURE_2D, texture_id_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id_, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw FramebufferError {"The framebuffer is incomplete."};
    }

    Unbind();
}

auto Framebuffer::Bind() -> void {
    glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer_id_);
    glBindRenderbuffer(GL_RENDERBUFFER, render_buffer_id_);
}

auto Framebuffer::Unbind() -> void {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

Framebuffer::~Framebuffer() {
    if (frame_buffer_id_) {
        glDeleteFramebuffers(1, &frame_buffer_id_);
        glDeleteRenderbuffers(1, &render_buffer_id_);
        glDeleteTextures(1, &texture_id_);
    }
}