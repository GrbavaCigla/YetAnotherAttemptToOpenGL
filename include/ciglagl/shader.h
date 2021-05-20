#pragma once
#include <cerrno>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <spdlog/spdlog.h>

std::string getFileContents(const std::string &filepath);

enum CompileType {
    PROGRAM,
    FRAGMENT,
    VERTEX,
};

class Shader {
  public:
    GLuint ID;
    Shader(const std::string &vertexFilepath, const std::string &fragmentFilepath);
    ~Shader();

    void Activate();

  private:
    void CompileMessages(GLuint shader, CompileType type);
};