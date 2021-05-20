#include <ciglagl/ebo.h>
#include <spdlog/spdlog.h>

EBO::EBO(GLuint *indices, GLsizeiptr size) {
    spdlog::info("Generating EBO buffer.");
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

EBO::~EBO() {
    spdlog::info("Deleting EBO buffer.");
    glDeleteBuffers(1, &ID);
}

void EBO::Bind() {
    spdlog::info("Binding EBO buffer to GL_ELEMENT_ARRAY_BUFFER.");
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind() {
    spdlog::info("Unbinding EBO buffer.");
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}