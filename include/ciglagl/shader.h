#pragma once
#include <cerrno>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

std::string getFileContents(const std::string &filepath);

class Shader {
  public:
    GLuint id;
    Shader(const std::string &vertex_filepath,
           const std::string &fragment_filepath);
    ~Shader();

    void activate();
};