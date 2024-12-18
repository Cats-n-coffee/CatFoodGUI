#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "../resourceProcessing/Texture2DPNG.h"

class Cat
{
public:
	Cat(const std::string& name, const std::string& texturePath);
	~Cat();

	inline unsigned int GetCatTextureID() const { return m_TextureID; }
	inline const std::vector<float> GetCatVertices() { return m_Vertices; }

private:
	std::string m_Name = "";
	std::string m_TexturePath = "";
	unsigned int m_TextureID = 0;
	
	std::vector<float> m_Vertices; // TODO: copy data over

	glm::vec3 m_TranslateVector = glm::vec3(0.0f);
	float m_RotateDegrees = 0.0f;
	short m_CatDirection = 0; // Keep this here?

	void const SetCatVertices();
	void SetCatTexture(const std::string& texture);
};