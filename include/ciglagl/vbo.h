#pragma once

#include <glad/glad.h>
#include <spdlog/spdlog.h>

class VBO {
  public:
    GLuint ID;
    VBO(GLfloat *vertices, GLsizeiptr size);
    ~VBO();

    void Bind();
    void Unbind();
};