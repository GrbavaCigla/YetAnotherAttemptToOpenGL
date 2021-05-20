#pragma once
#include <cerrno>
#include <fstream>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

std::string getFileContents(const std::string &filepath);

class Shader {
  public:
    GLuint ID;
    Shader(const std::string &vertexFilepath,
           const std::string &fragmentFilepath);
    ~Shader();

    void Activate();
};