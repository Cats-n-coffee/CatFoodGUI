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
	// TODO: verify key press and repeat logic
	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		m_CatObject.MoveRight();
	}
	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		m_CatObject.MoveLeft();
	}
	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		m_CatObject.MoveUp();
	}
	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		m_CatObject.MoveDown();
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
