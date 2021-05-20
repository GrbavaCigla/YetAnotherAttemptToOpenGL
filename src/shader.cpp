#include <ciglagl/shader.h>

#define COMPILE_ERROR_BUFFER_SIZE 1024

std::string getFileContents(const std::string &filepath) {
    std::ifstream file(filepath, std::ios::binary);

    if (file) {
        std::string contents;
        file.seekg(0, std::ios::end);
        contents.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(&contents[0], contents.size());
        file.close();
        return contents;
    } else {
        spdlog::error("Failed to read from \"{}\".", filepath);
        throw errno;
    }
}

Shader::Shader(const std::string &vertexFilepath,
               const std::string &fragmentFilepath) {
    spdlog::info("Opening vertex shader code.");
    std::string vertexShaderCode = getFileContents(vertexFilepath);

    spdlog::info("Opening fragment shader code.");
    std::string fragmentShaderCode = getFileContents(fragmentFilepath);

    const char *pVertexShaderCode = vertexShaderCode.c_str();
    const char *pFragmentShaderCode = fragmentShaderCode.c_str();

    spdlog::info("Compiling vertex shader source.");
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &pVertexShaderCode, NULL);
    glCompileShader(vertexShader);

    GLint vertexCompiled;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexCompiled);
    if (vertexCompiled != GL_TRUE) {
        GLsizei logLength = 0;
        GLchar message[COMPILE_ERROR_BUFFER_SIZE];
        glGetShaderInfoLog(vertexShader, COMPILE_ERROR_BUFFER_SIZE, &logLength,
                           message);
        spdlog::error("Vertex shader compile error:\n{}", message);
    }

    spdlog::info("Compiling fragment shader source.");
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &pFragmentShaderCode, NULL);
    glCompileShader(fragmentShader);

    GLint fragmentCompiled;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentCompiled);
    if (fragmentCompiled != GL_TRUE) {
        GLsizei logLength = 0;
        GLchar message[COMPILE_ERROR_BUFFER_SIZE];
        glGetShaderInfoLog(fragmentShader, COMPILE_ERROR_BUFFER_SIZE,
                           &logLength, message);
        spdlog::error("Fragment shader compile error:\n{}", message);
    }

    spdlog::info("Creating shader program.");
    ID = glCreateProgram();

    spdlog::info("Attaching shaders to shader program.");
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    spdlog::info("Cleaning up shaders.");
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    spdlog::info("Deleting shader program.");
    glDeleteProgram(ID);
}

void Shader::Activate() { glUseProgram(ID); }
