#include <ciglagl/vao.h>

VAO::VAO() {
    spdlog::info("Generating VAO vertex array.");
    glGenVertexArrays(1, &ID);
}

VAO::~VAO() {
    spdlog::info("Deleting VAO vertex array.");
    glDeleteVertexArrays(1, &ID);
}

void VAO::LinkVBO(VBO &VBO, GLuint layout) {
    spdlog::info("Linking VBO to VAO.");
    VBO.Bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
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