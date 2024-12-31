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

class Cat
{
public:
	Cat();
	Cat(const std::string& name, const std::string& texturePath);

	void UpdateObject(glm::mat4& orthographicProjection);
	void RenderObject();

private:
	std::string m_Name = "";
	std::string m_TexturePath = "";
	unsigned int m_TextureID = 0;
	
	std::vector<float> m_Vertices; // TODO: copy data over

// 	unsigned int m_VAO = 0, m_VBO = 0;
	VAO m_CatVAO;
	VBO m_CatVBO;
	ShaderProgram m_ShaderProgram;
	unsigned int m_MvpLocation = 0;
	
	// MVP things
	glm::mat4 m_ModelViewProjection = glm::mat4(1.0f);
	glm::vec3 m_TranslateVector = glm::vec3(0.0f);
	float m_RotateDegrees = 0.0f;
	short m_CatDirection = 0; // Keep this here?

	void const SetCatVertices();
	void SetCatTexture(const std::string& texture);
};