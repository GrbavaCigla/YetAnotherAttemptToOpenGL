#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/common.h>
#include <spdlog/spdlog.h>

#include <ciglagl/shader.h>
#include <ciglagl/vao.h>
#include <ciglagl/vbo.h>
#include <ciglagl/ebo.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define MSAA_SAMPLES 16

// Vertices coordinates
GLfloat vertices[] = {
    -0.5f,     -0.5f * float(sqrt(3)) / 3,    0.0f, // Lower left corner
    0.5f,      -0.5f * float(sqrt(3)) / 3,    0.0f, // Lower right corner
    0.0f,      0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6,     0.0f, // Inner left
    0.5f / 2,  0.5f * float(sqrt(3)) / 6,     0.0f, // Inner right
    0.0f,      -0.5f * float(sqrt(3)) / 3,    0.0f  // Inner down
};

// Indices for vertices order
GLuint indices[] = {
    0, 3, 5, // Lower left triangle
    3, 2, 4, // Lower right triangle
    5, 4, 1  // Upper triangle
};

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, MSAA_SAMPLES);

    GLFWwindow *window =
        glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "CiglaGL", NULL, NULL);

    if (window == NULL) {
        spdlog::critical("Failed to create GLFW window.");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glEnable(GL_MULTISAMPLE);

    Shader shaderProgram(
        "../res/shaders/default.vert",
        "../res/shaders/default.frag"
    );

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkVBO(VBO1, 0);
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();

        spdlog::level::level_enum cur_lvl = spdlog::get_level();
        spdlog::set_level(spdlog::level::off);
        VAO1.Bind();
        spdlog::set_level(cur_lvl);
        
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}