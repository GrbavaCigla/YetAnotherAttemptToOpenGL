#pragma once

#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include <ciglagl/vbo.h>

class VAO {
  public:
    GLuint ID;
    VAO();
    ~VAO();

    void LinkAttrib(VBO &VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset);
    void Bind();
    void Unbind();
};