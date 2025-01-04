#pragma once

#include <vector>
#include <string>
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

	void UpdateObject(glm::mat4& orthographicProjection);
	void RenderObject();

private:
	std::vector<float> m_Vertices;
	unsigned int m_FoodTextureID = 0;

	VAO m_VAO;
	VBO m_VBO;
	ShaderProgram m_ShaderProgram;
	unsigned int m_MvpLocation = 0;
	
	// MVP business
	glm::vec3 m_TranslateVector = glm::vec3(0.6f, 0.6f, 0.0f);
	glm::mat4 m_ModelViewProjection = glm::mat4(1.0f);

	void Init(const std::string& texturePath); // Maybe this should return a bool to let the caller know if it was a success
	void SetVertices();
	void SetFoodTexture(const std::string& texturePath);
};
