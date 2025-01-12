#pragma once

#include <iostream>
#include <glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "GameObjects/Cat.h"
#include "GameObjects/Food.h"

class Game
{
public:
	Game();

	void Init();

	void ProcessKeyEvents(int key, int scancode, int action, int mods);

	void Update();
	void Render();
	
	inline glm::mat4 GetOrthographicProjection() const { return m_OrthographicProjection; }

private:
	enum Direction {
		down,
		up,
		left,
		right,
	};
	// Objects & texture
	Cat m_CatObject;
	Food m_FoodFirstObject;

	// Collision test
	bool CheckCollisionWithCat(Direction direction);

	// Transformations
    glm::mat4 m_OrthographicProjection = glm::ortho(
       -1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f
    );
};