#pragma once

#include <vector>
#include <string>
#include <random>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "../../../resourceProcessing/Texture2DPNG.h"
#include "../Rendering/ShaderProgram.h"
#include "../Rendering/VAO.h"
#include "../Rendering/VBO.h"

class Food
{
public:
	Food();
	Food(const std::string& texturePath);
	~Food();

	std::vector<glm::vec3> GetBoundingBox() const { return m_BoundingBox; }

	void UpdateObject(glm::mat4& orthographicProjection, double deltaTime);
	void RenderObject();

	// Move function are only used/directed by the program
	bool MoveUp();
	bool MoveDown();
	bool MoveLeft();
	bool MoveRight();

	void UpdateFoodPosition();

private:
	enum Direction {
		down,
		up,
		left,
		right,
	};

	std::vector<float> m_Vertices;
	unsigned int m_FoodTextureID = 0;

	VAO m_VAO;
	VBO m_VBO;
	ShaderProgram m_ShaderProgram;
	unsigned int m_MvpLocation = 0;
	
	// MVP business
	glm::vec3 m_ScalingVector = glm::vec3(0.5f, 0.5f, 0.5f);
	float m_RotateDegrees = 0.0f;
	glm::vec3 m_TranslateVector = glm::vec3(-0.6f, 0.6f, 0.0f);
	glm::mat4 m_ModelViewProjection = glm::mat4(1.0f);

	// Collisions
	std::vector<glm::vec3> m_BoundingBox = { // this needs to be automated
		glm::vec3(-0.25f, 0.25f, 0.0f), // top left
		glm::vec3(0.25f, 0.25f, 0.0f), // top right
		glm::vec3(0.25f, -0.25f, 0.0f), // bottom right
		glm::vec3(-0.25f, -0.25f, 0.0f), // bottom left
	};

	// Food movement/AI lol
	double m_deltaTime = 0.0;
	float m_Velocity = 2.0f; // should be called speed since this is a scalar
	float m_Force = 2.0f;
	float m_Mass = 1.0f;

	bool changeDirection = false;
	Direction currentDirection = Direction::right;
	short m_Uturns = 0;

	// Methods
	void Init(const std::string& texturePath); // Maybe this should return a bool to let the caller know if it was a success
	void SetVertices();
	void SetFoodTexture(const std::string& texturePath);

	// Collisions methods - to be moved
	void UpdateBoundingBox(std::vector<glm::vec3>& boundingBox, Direction direction);
	void TempBoundingBoxTransform();
};
