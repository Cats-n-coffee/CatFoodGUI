#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "../../../resourceProcessing/Texture2DPNG.h"
#include "../Rendering/ShaderProgram.h"
#include "../Rendering/VAO.h"
#include "../Rendering/VBO.h"

const float FACE_RIGHT = 270.0f;
const float FACE_LEFT = 90.0f;
const float FACE_UP = 180.0f;
const float FACE_DOWN = 0.0f;

class Cat
{
public:
	Cat();
	Cat(const std::string& name, const std::string& texturePath);

	void UpdateObject(glm::mat4& orthographicProjection);
	void RenderObject();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

private:
	enum Direction {
		down,
		up,
		left,
		right,
	};

	std::string m_Name = "";
	std::string m_TexturePath = "";
	unsigned int m_TextureID = 0;
	
	std::vector<float> m_Vertices; // TODO: copy data over

	VAO m_CatVAO;
	VBO m_CatVBO;
	ShaderProgram m_ShaderProgram;
	unsigned int m_MvpLocation = 0;
	
	// MVP things
	float m_RotateDegrees = FACE_DOWN;
	glm::vec3 m_TranslateVector = glm::vec3(0.0f);
	glm::mat4 m_ModelViewProjection = glm::mat4(1.0f);

	short m_CatDirection = Direction::down;

	// Collisions
	std::vector<glm::vec3> m_BoundingBox = { // this needs to be automated
		glm::vec3(-0.25f, 0.25f, 0.0f), // top left
		glm::vec3(0.25f, 0.25f, 0.0f), // top right
		glm::vec3(0.25f, -0.25f, 0.0f), // bottom right
		glm::vec3(-0.25f, -0.25f, 0.0f), // bottom left
	};

	// Methods
	void Init(const std::string& name, const std::string& texturePath);
	void const SetCatVertices();
	void SetCatTexture(const std::string& texture);

	// Collisions methods - to be moved
	void UpdateBoundingBox(std::vector<glm::vec3>& boundingBox, Direction direction);
};