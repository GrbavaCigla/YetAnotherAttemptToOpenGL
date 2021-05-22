#pragma once
#include <glad/glad.h>
#include <ciglagl/shader.h>

class Texture {
  public:
    GLuint ID;
    GLenum type;
    Texture(const std::string &imagePath, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
    ~Texture();

    void TextureUnit(Shader &shader, const char *uniform, GLuint unit);
    void Bind();
    void Unbind();
};