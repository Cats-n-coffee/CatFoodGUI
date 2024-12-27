#pragma once

#include <iostream>
#include <glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Rendering/ShaderProgram.h"
#include "GameObjects/Cat.h"

class Game
{
public:
	Game();

	void Init();

	void ProcessKeyEvents(int key, int scancode, int action, int mods);

	void Update();
	void Render();
	
	inline unsigned int GetCatTexture() const { return m_CatTexture; }
	inline glm::mat4 GetOrthographicProjection() const { return m_OrthographicProjection; }
	inline unsigned int GetMVPLocation() const { return m_MvpLocation; }
	inline unsigned int GetVAO() const { return m_VAO; }

private:
	// Objects & texture
	Cat m_CatObject;
	unsigned int m_CatTexture = 0;
	std::vector<float> m_CatVertices = {};

	// Transformations
    glm::mat4 m_OrthographicProjection = glm::ortho(
       -1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f
    );

	// OpenGL state
	unsigned int m_VAO = 0, m_VBO = 0;

	// Shader program
	ShaderProgram m_ShaderProgram;

	// Uniforms
	unsigned int m_MvpLocation = 0;

	// TODO: what we do with this?
	glm::vec3 translateRect = glm::vec3(0.0f, 0.0f, 0.0f);
	float rotateDegrees = 0.0f;

	short playerDirection = 0;
};