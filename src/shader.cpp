#include <ciglagl/shader.h>

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

Shader::Shader(const std::string &vertex_filepath,
               const std::string &fragment_filepath) {
    spdlog::info("Opening vertex shader code.");
    std::string vertex_shader_code = getFileContents(vertex_filepath);

    spdlog::info("Opening fragment shader code.");
    std::string fragment_shader_code = getFileContents(fragment_filepath);

    const char *vertex_shader_code_ptr = vertex_shader_code.c_str();
    const char *fragment_shader_code_ptr = fragment_shader_code.c_str();

    spdlog::info("Compiling vertex shader source.");
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_code_ptr, NULL);
    glCompileShader(vertex_shader);

    GLint vertex_compiled;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vertex_compiled);
    if (vertex_compiled != GL_TRUE) {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(vertex_shader, 1024, &log_length, message);
        spdlog::error("Vertex shader compile error:\n{}", message);
    }

    spdlog::info("Compiling fragment shader source.");
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_code_ptr, NULL);
    glCompileShader(fragment_shader);

    GLint fragment_compiled;
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &fragment_compiled);
    if (fragment_compiled != GL_TRUE) {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(fragment_shader, 1024, &log_length, message);
        spdlog::error("Fragment shader compile error:\n{}", message);
    }

    spdlog::info("Creating shader program.");
    id = glCreateProgram();

    spdlog::info("Attaching shaders to shader program.");
    glAttachShader(id, vertex_shader);
    glAttachShader(id, fragment_shader);
    glLinkProgram(id);

    spdlog::info("Cleaning up shaders.");
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

Shader::~Shader() {
    spdlog::info("Deleting shader program.");
    glDeleteProgram(id);
}

void Shader::activate() { glUseProgram(id); }
