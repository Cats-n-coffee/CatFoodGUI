#pragma once

#include <iostream>
#include <string>
#include <glew.h>
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"

struct Vector2 {
    float x;
    float y;
};

float vertices[6] = {
    0.5f, 0.5f,
    0.5f, -0.5f,
    0.0f, 0.5f
};

static const char* vertexShaderCode =
"#version 330\n"
"layout (location = 0) in vec2 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(position, 0.0f, 1.0f);\n"
"}\n";

static const char* fragmentShaderCode =
"#version 330\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
"}\n";

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // GLEW
    glewExperimental = GL_TRUE;

    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        printf("Error with GLEW");
        return -1;
    }

    /*std::string vertexFileContent = ReadResourceFileToStr("resources/shaders/vertex.shader");
    const char* vertexCodePtr = vertexFileContent.c_str();

    std::string fragmentFileContent = ReadResourceFileToStr("resources/shaders/fragment.shader");
    const char* fragmentCodePtr = fragmentFileContent.c_str();*/

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    ShaderProgram shaderProgram = ShaderProgram(
        "resources/shaders/vertex.shader",
        "resources/shaders/fragment.shader"
    );

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

	return 0;
}