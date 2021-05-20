#include <ciglagl/vao.h>

VAO::VAO() {
    spdlog::info("Generating VAO vertex array.");
    glGenVertexArrays(1, &ID);
}

VAO::~VAO() {
    spdlog::info("Deleting VAO vertex array.");
    glDeleteVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO &VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset) {
    spdlog::info("Linking VBO to VAO.");
    VBO.Bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

void VAO::Bind() {
    spdlog::info("Binding VAO vertex array.");
    glBindVertexArray(ID);
}

void VAO::Unbind() {
    spdlog::info("Unbinding VAO vertex array.");
    glBindVertexArray(0);
}