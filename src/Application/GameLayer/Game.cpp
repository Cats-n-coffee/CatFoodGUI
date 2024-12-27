#include "Game.h"

Game::Game()
{}

void Game::Init()
{
	// here add object init like cats and food

    // ========== Cat Object Test
    m_CatObject = Cat("Kiki", "resources/images/CatSprite256.png");
    m_CatTexture = m_CatObject.GetCatTextureID();
    m_CatVertices = m_CatObject.GetCatVertices();

    // ========== VAO, VBO
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(catVertices), &catVertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, m_CatVertices.size() * sizeof(float), &m_CatVertices[0], GL_STATIC_DRAW);
    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_ShaderProgram = ShaderProgram(
        "resources/shaders/vertex.shader",
        "resources/shaders/fragment.shader"
    );

    // Assign uniform
    m_MvpLocation = glGetUniformLocation(m_ShaderProgram.getProgramId(), "modelViewProjection");
}

void Game::ProcessKeyEvents(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) // TODO: need viewport bounds
	{
		if (playerDirection != 3)
		{
			rotateDegrees = 270.0f;
			playerDirection = 3;
		}
		translateRect.x += 0.1f;
		std::cout << "prssed " << translateRect.x << std::endl;
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) // need viewport bounds
	{
		if (playerDirection != 1)
		{
			rotateDegrees = 90.0f;
			playerDirection = 1;
		}
		translateRect.x -= 0.1f;
		std::cout << "prssed " << translateRect.x << std::endl;
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) // need viewport bounds
	{
		if (playerDirection != 2)
		{
			rotateDegrees = 180.0f;
			playerDirection = 2;
		}
		translateRect.y += 0.1f;
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) // TODO: viewport bounds
	{
		if (playerDirection != 0)
		{
			rotateDegrees = 0.0f;
			playerDirection = 0;
		}
		translateRect.y -= 0.1f;
	}
}

void Game::Update()
{
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.7f, 0.7f, 0.7f));
	glm::mat4 rotation = glm::rotate(glm::radians(rotateDegrees), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), translateRect);
	glm::mat4 modelMatrix = translation * rotation * scale;
	glm::mat4 modelViewProjection = m_OrthographicProjection * modelMatrix;

	glUniformMatrix4fv(m_MvpLocation, 1, GL_FALSE, &modelViewProjection[0][0]);

}

void Game::Render()
{
	glBindTexture(GL_TEXTURE_2D, m_CatTexture);
	glBindVertexArray(m_VAO); // this is needed here - why? 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glDrawArrays(GL_TRIANGLES, 0, 36);
}
