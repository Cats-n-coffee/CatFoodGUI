#pragma once

#include <iostream>
#include <string>
#include <glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "ShaderProgram.h"


float vertices[8] = {
    -0.5f, -0.5f, // bottom left
    -0.5f, -0.0f, // top left
    0.0f, 0.0f, // top right
    0.0f, -0.5f, // bottom right
};

unsigned int indices[6] = {
    0, 1, 2,
    0, 3, 2
};

// https://gamedev.stackexchange.com/questions/174463/which-is-a-better-way-for-moving-3d-objects-in-opengl

int width = 640;
int height = 480;

glm::vec3 translateRect = glm::vec3(0.1f);

static void keyEvents(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        translateRect.x -= 0.1f;
        std::cout << "prssed " << translateRect.x << std::endl;
    }
}

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
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
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

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    ShaderProgram shaderProgram = ShaderProgram(
        "resources/shaders/vertex.shader",
        "resources/shaders/fragment.shader"
    );

    // Transformations
    glm::mat4 viewMatrix = glm::lookAt( // Camera, world moves around it
        glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f)
    );
    //glm::mat4 projectionMatrix = glm::perspective( // Gives the perspective using the z coords
    //    glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f
    //);
    glm::mat4 orthographicProjection = glm::ortho(
       -2.0f, 2.0f, -2.0f, 2.0f, 0.1f, 100.0f
    );

    // User input
    glfwSetKeyCallback(window, keyEvents);

    // Get the uniform location in the program
    unsigned int mvpLocation = glGetUniformLocation(shaderProgram.getProgramId(), "modelViewProjection");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glBindVertexArray(VAO); // this is needed here - why? 
        glClear(GL_COLOR_BUFFER_BIT);

        // Update the MVP in shader
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), translateRect); // Should be scale, rotation, translation
        glm::mat4 modelViewProjection = orthographicProjection * viewMatrix * modelMatrix;

        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &modelViewProjection[0][0]);

        // Draw
        glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, (void*)0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

	return 0;
}