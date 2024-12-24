#include "Application.h"

Application::Application()
{}

void Application::Init()
{
	
    Window* gameWindow = new Window();
    gameWindow->Init(800, 600);
    GLFWwindow* window = gameWindow->GetWindow();

    // ========== Cat Object Test
    Cat* catObject = new Cat("Kiki", "resources/images/CatSprite256.png");
    unsigned int catTexture = catObject->GetCatTextureID();
    const std::vector<float> catVertices = catObject->GetCatVertices();

    // ========== Textures
    // unsigned int catTexture = generateTexture2DPNG("resources/images/CatSprite256.png");

    // ========== VAO, VBO
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(catVertices), &catVertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, catVertices.size() * sizeof(float), &catVertices[0], GL_STATIC_DRAW);
    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

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

    /*
    while(Game.IsRunning)
    {
        Input = GetInput();
        Game.Update(Input);
        Display(Game);
    }
    */

    // Get the uniform location in the program
    unsigned int mvpLocation = glGetUniformLocation(shaderProgram.getProgramId(), "modelViewProjection");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glBindTexture(GL_TEXTURE_2D, catTexture);
        glBindVertexArray(VAO); // this is needed here - why? 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update the MVP in shader
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.7f, 0.7f, 0.7f));
        glm::mat4 rotation = glm::rotate(glm::radians(rotateDegrees), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), translateRect);
        glm::mat4 modelMatrix = translation * rotation * scale;
        glm::mat4 modelViewProjection = orthographicProjection * modelMatrix;

        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &modelViewProjection[0][0]);

        // Draw
        glDrawArrays(GL_TRIANGLES, 0, 36);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
}

Application::~Application()
{}