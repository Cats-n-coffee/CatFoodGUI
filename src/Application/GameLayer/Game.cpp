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

	// ========== Tilemap Object Test
	m_TilemapObject = Tilemap("resources/images/Tilemap1.png");
}

void Game::ProcessKeyEvents(int key, int scancode, int action, int mods)
{
	// TODO: verify key press and repeat logic
	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		bool isColliding = CheckCollisionWithCat(Direction::right);
		if (!isColliding) m_CatObject.MoveRight();
	}
	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		bool isColliding = CheckCollisionWithCat(Direction::left);
		if (!isColliding) m_CatObject.MoveLeft();
	}
	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		bool isColliding = CheckCollisionWithCat(Direction::up);
		if (!isColliding) m_CatObject.MoveUp();
	}
	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		bool isColliding = CheckCollisionWithCat(Direction::down);
		if (!isColliding) m_CatObject.MoveDown();
	}
}

void Game::Update(double deltaTime)
{
	{ // Update MVP for cat
		m_CatObject.UpdateObject(m_OrthographicProjection);
	}
	
	{ // Update MVP for food
		m_FoodFirstObject.UpdateObject(m_OrthographicProjection, deltaTime);
	}

	{
		m_TilemapObject.UpdateObject(m_OrthographicProjection);
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

	{
		m_TilemapObject.RenderObject();
	}
}

bool Game::CheckCollisionWithCat(Direction direction)
{
	std::vector<glm::vec3> catBox = m_CatObject.GetBoundingBox();
	std::vector<glm::vec3> foodBox = m_FoodFirstObject.GetBoundingBox();
	float foodXArr[2] = { foodBox[0].x, foodBox[0].x };
	float foodYArr[2] = { foodBox[0].y, foodBox[0].y };

	for (auto& foodVertex : foodBox)
	{
		if (foodVertex.x < foodXArr[0]) foodXArr[0] = foodVertex.x;
		if (foodVertex.x > foodXArr[1]) foodXArr[1] = foodVertex.x;

		if (foodVertex.y < foodYArr[0]) foodYArr[0] = foodVertex.y;
		if (foodVertex.y > foodYArr[1]) foodYArr[1] = foodVertex.y;
	}

	float xIncrement = 0.0f;
	float yIncrement = 0.0f;

	if (direction == Direction::right) {
		xIncrement = 0.01f;
		yIncrement = 0.0f;
	}
	if (direction == Direction::left) {
		xIncrement = -0.01f;
		yIncrement = 0.0f;
	}
	if (direction == Direction::up) {
		xIncrement = 0.0f;
		yIncrement = 0.01f;
	}
	if (direction == Direction::down) {
		xIncrement = 0.0f;
		yIncrement = -0.01f;
	}
	std::cout << "fish X: " << foodXArr[0] << " , " << foodXArr[1] << " | fish Y: " << foodYArr[0] << " , " << foodYArr[1] << std::endl;

	// Compare the min and max of both X and Y of the food
	// to the X and Y of each cat vertex
	for (auto& vertex : catBox)
	{
		bool xCheck = ((vertex.x + xIncrement) >= foodXArr[0]) && ((vertex.x + xIncrement) <= foodXArr[1]);
		bool yCheck = ((vertex.y + yIncrement) >= foodYArr[0]) && ((vertex.y + yIncrement) <= foodYArr[1]);

		if (
			(xCheck)
			&& (yCheck)
			) return true;
	}

	return false;
}
