#pragma once

#include <iostream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "vendors/stb_image.h"
#include <glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "ShaderProgram.h"


float vertices[180] = { // total 180
    // front - triangle 1
    -0.25f, -0.25f, -0.1f, 0.5f, 0.0f, // front - bottom left
    0.25f, -0.25f, -0.1f, 1.0f, 0.0f,// front - bottom right
    0.25f, 0.25f, -0.1f, 1.0f, 0.5f, // front - top right
    // front - triangle 2
    -0.25f, -0.25f, -0.1f, 0.5f, 0.0f, // front - bottom left
    0.25f, 0.25f, -0.1f, 1.0f, 0.5f,// front - top right
    -0.25f, 0.25f, -0.1f, 0.5f, 0.5f,// front - top left
    // left - triangle 1
    -0.25f, -0.25f, -0.6f, 0.5f, 0.5f, // left - bottom back
    -0.25f, -0.25f, -0.1f, 1.0f, 0.5f, // left - bottom front
    -0.25f, 0.25f, -0.1f, 1.0f, 1.0f, // left - top front
    // left - triangle 2
    -0.25f, -0.25f, -0.6f, 0.5f, 0.5f, // left - bottom back
    -0.25f, 0.25f, -0.6f, 0.5f, 1.0f, // left - top back
    -0.25f, 0.25f, -0.1f, 1.0f, 1.0f, // left - top front
    // back - triangle 1
    -0.25f, -0.25f, -0.6f, 0.0f, 0.5f, // back - bottom left
    0.25f, -0.25f, -0.6f, 0.5f, 0.5f, // back - bottom right
    0.25f, 0.25f, -0.6f, 0.5f, 1.0f, // back - top right
    // back - triangle 2
    0.25f, 0.25f, -0.6f, 0.5f, 1.0f, // back - top right
    -0.25f, 0.25f, -0.6f, 0.0f, 1.0f, // back - top left
    -0.25f, -0.25f, -0.6f, 0.0f, 0.5f, // back - bottom left
    // right - triangle 1
    0.25f, -0.25f, -0.6f, 0.5f, 0.0f, // right - bottom back
    0.25f, 0.25f, -0.6f, 0.5f, 0.5f, // right - top back
    0.25f, 0.25f, -0.1f, 0.0f, 0.5f, // right - top front
    // right - triangle 2
    0.25f, 0.25f, -0.1f, 0.0f, 0.5f, // right - top front
    0.25f, -0.25f, -0.1f, 0.0f, 0.0f, // right - bottom front
    0.25f, -0.25f, -0.6f, 0.5f, 0.0f, // right - bottom back
    // top - triangle 1
    -0.25f, 0.25f, -0.1f, 0.0f, 0.0f, // front - top left
    0.25f, 0.25f, -0.1f, 1.0f, 0.0f, // front - top right
    0.25f, 0.25f, -0.6f, 1.0f, 1.0f, // back - top right
    // top - triangle 2
    0.25f, 0.25f, -0.6f, 1.0f, 1.0f, // back - top right
    -0.25f, 0.25f, -0.6f, 0.0f, 1.0f, // back - top left
    -0.25f, 0.25f, -0.1f, 0.0f, 0.0f, // front - top left
    // bottom - triangle 1
    -0.25f, -0.25f, -0.1f, 0.0f, 0.0f, // front - bottom left
    0.25f, -0.25f, -0.1f, 1.0f, 0.0f, // front - bottom right
    0.25f, -0.25f, -0.6f, 1.0f, 1.0f, // back - bottom right
    // bottom - triangle 2
    0.25f, -0.25f, -0.6f, 1.0f, 1.0f, // back - bottom right
    -0.25f, -0.25f, -0.6f, 0.0f, 1.0f, // back - bottom left
    -0.25f, -0.25f, -0.1f, 0.0f, 0.0f, // front - bottom left
};

//unsigned int indices[36] = {
//    0, 1, 2, 0, 2, 3, // front face
//    4, 0, 3, 4, 7, 3, // left face
//    4, 5, 6, 4, 7, 6, // back face
//    1, 5, 6, 1, 2, 6, // right face
//    2, 3, 6, 3, 7, 6, // top face
//    0, 1, 5, 1, 4, 5, // bottom face
//};

// https://gamedev.stackexchange.com/questions/174463/which-is-a-better-way-for-moving-3d-objects-in-opengl

int width = 640;
int height = 480;

glm::vec3 translateRect = glm::vec3(0.0f, 0.0f, 0.0f);
float rotateDegrees = 0.0f;

static void keyEvents(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        translateRect.x += 0.1f;
        std::cout << "prssed " << translateRect.x << std::endl;
    }
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        translateRect.x -= 0.1f;
        std::cout << "prssed " << translateRect.x << std::endl;
    }
    // turn left: h
    // turn right: l
    // turn up: k
    // turn down: j
    if (key == GLFW_KEY_H && action == GLFW_PRESS) // Left
    {
        rotateDegrees = 90.0f;
        std::cout << "rotated: " << rotateDegrees << std::endl;
    }
    if (key == GLFW_KEY_L && action == GLFW_PRESS) // Right
    {
        rotateDegrees = 270.0f;
        std::cout << "rotated: " << rotateDegrees << std::endl;
    }
    if (key == GLFW_KEY_K && action == GLFW_PRESS) // Up/back
    {
        rotateDegrees = 180.0f;
        std::cout << "rotated: " << rotateDegrees << std::endl;
    }
    if (key == GLFW_KEY_J && action == GLFW_PRESS) // Down/front
    {
        rotateDegrees = 0.0f;
        std::cout << "rotated: " << rotateDegrees << std::endl;
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
    glfwSwapInterval(1); // vsync
    glEnable(GL_DEPTH_TEST);

    // GLEW
    glewExperimental = GL_TRUE;

    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        printf("Error with GLEW");
        return -1;
    }

    // ========== Textures
    unsigned int catSpriteTexture;
    glGenTextures(1, &catSpriteTexture);

    glBindTexture(GL_TEXTURE_2D, catSpriteTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int imageWidth, imageHeight, nrChannel;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* imageData = stbi_load("resources/images/CatSprite256.png", &imageWidth, &imageHeight, &nrChannel, 0);

    if (imageData)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(imageData);

    // ========== VAO, VBO
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    ShaderProgram shaderProgram = ShaderProgram(
        "resources/shaders/vertex.shader",
        "resources/shaders/fragment.shader"
    );

    // Transformations
    glm::mat4 orthographicProjection = glm::ortho(
       -1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f
    );

    // User input
    glfwSetKeyCallback(window, keyEvents);

    // Get the uniform location in the program
    unsigned int mvpLocation = glGetUniformLocation(shaderProgram.getProgramId(), "modelViewProjection");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glBindTexture(GL_TEXTURE_2D, catSpriteTexture);
        glBindVertexArray(VAO); // this is needed here - why? 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update the MVP in shader
        glm::mat4 rotation = glm::rotate(glm::radians(rotateDegrees), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), translateRect);
        glm::mat4 modelMatrix = translation * rotation; // Should be scale, rotation, translation
        // glm::mat4 modelMatrix = glm::mat4(1.0f);
        /*glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 modelViewProjection = orthographicProjection * modelMatrix;*/
        glm::mat4 modelViewProjection = glm::mat4(1.0f) * modelMatrix;

        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &modelViewProjection[0][0]);

        // Draw
        // glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, (void*)0);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

	return 0;
}