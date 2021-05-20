#include <ciglagl/shader.h>
#include <spdlog/spdlog.h>

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

Shader::Shader(const std::string &vertexFilepath, const std::string &fragmentFilepath) {
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
    CompileMessages(vertexShader, VERTEX);

    spdlog::info("Compiling fragment shader source.");
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &pFragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
    CompileMessages(fragmentShader, FRAGMENT);

    spdlog::info("Creating shader program.");
    ID = glCreateProgram();

    spdlog::info("Attaching shaders to shader program.");
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    CompileMessages(ID, PROGRAM);

    spdlog::info("Cleaning up shaders.");
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    spdlog::info("Deleting shader program.");
    glDeleteProgram(ID);
}

void Shader::Activate() { glUseProgram(ID); }

void Shader::CompileMessages(GLuint shader, CompileType type) {
    GLint compiled;

    if (type == PROGRAM) {
        glGetProgramiv(shader, GL_COMPILE_STATUS, &compiled);
    } else {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    }

    if (compiled == GL_FALSE) {
        GLchar message[COMPILE_ERROR_BUFFER_SIZE];
        if (type == PROGRAM) {
            glGetProgramInfoLog(shader, COMPILE_ERROR_BUFFER_SIZE, NULL, message);
        } else {
            glGetShaderInfoLog(shader, COMPILE_ERROR_BUFFER_SIZE, NULL, message);
        }

        switch (type) {
        case PROGRAM:
            spdlog::error("Program linking error:\n{}", message);
            break;
        case FRAGMENT:
            spdlog::error("Fragment shader compiling error:\n{}", message);
            break;
        case VERTEX:
            spdlog::error("Vertex shader compiling error:\n{}", message);
            break;
        }
    }
}
