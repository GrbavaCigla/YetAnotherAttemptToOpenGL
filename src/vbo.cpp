#include <ciglagl/vbo.h>
#include <spdlog/spdlog.h>

VBO::VBO(GLfloat *vertices, GLsizeiptr size) {
    spdlog::info("Generating VBO buffer.");
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VBO::~VBO() {
    spdlog::info("Deleting VBO buffer.");
    glDeleteBuffers(1, &ID);
}

void VBO::Bind() {
    spdlog::info("Binding VBO buffer to GL_ARRAY_BUFFER.");
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() {
    spdlog::info("Unbinding VBO buffer.");
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}