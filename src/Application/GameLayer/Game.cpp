#include "Game.h"

Game::Game()
{}

void Game::Init()
{
	// here add object init like cats and food

    // ========== Cat Object Test
    m_CatObject = Cat("Kiki", "resources/images/CatSprite256.png");

	// ========== Food Object Test
	m_FoodFirstObject = Food("resources/images/FishSprite256.png");
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
	{ // Update MVP for cat
		m_CatObject.UpdateObject(m_OrthographicProjection);
	}
	
	{ // Update MVP for food
		m_FoodFirstObject.UpdateObject(m_OrthographicProjection);
	}
}

void Game::Render()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	{
		m_CatObject.RenderObject();
	}

	{
		m_FoodFirstObject.RenderObject();
	}
}
