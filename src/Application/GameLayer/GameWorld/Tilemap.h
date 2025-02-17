#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "../../../resourceProcessing/Texture2DPNG.h"
#include "../Rendering/VAO.h"
#include "../Rendering/VBO.h"
#include "../Rendering/ShaderProgram.h"

class Tilemap
{
public:
	Tilemap();
	Tilemap(const std::string& filePath);

	short tiles[64] = {
		3, 3, 3, 3, 3, 3, 3, 3,
		3, 0, 0, 0, 0, 0, 0, 3,
		3, 0, 0, 1, 1, 1, 1, 3,
		3, 0, 1, 1, 1, 1, 0, 3,
		3, 0, 2, 2, 2, 0, 0, 3,
		3, 0, 0, 0, 0, 0, 1, 3,
		3, 1, 1, 1, 1, 0, 1, 3,
		3, 1, 1, 1, 1, 1, 1, 3,
	};
	
	void UpdateObject(glm::mat4& orthographicProjection);
	void RenderObject();

private:
	unsigned int m_TextureID = 0;
	std::string m_TexturePath = "";
	VAO m_TilemapVAO;
	VBO m_TilemapVBO;
	ShaderProgram m_ShaderProgram;
	unsigned int m_MvpLocation = 0;

	glm::mat4 m_ModelViewProjection = glm::mat4(1.0f);

	enum TextureTileIndices {
		ground,
		water,
		waterEdge,
		bush,
	};

	// clockwise coordinates
	std::vector<std::vector<glm::vec2>> m_TextureTileCoords = {
		std::vector<glm::vec2> { // ground
			glm::vec2(0.0f, 1.0f), // top left
			glm::vec2(0.5f, 1.0f), // top right
			glm::vec2(0.5f, 0.5f), // bottom right
			glm::vec2(0.0f, 0.5f), // bottom left
		},
		std::vector<glm::vec2> { // water
			glm::vec2(0.5f, 1.0f),
			glm::vec2(1.0f, 1.0f),
			glm::vec2(1.0f, 0.5f),
			glm::vec2(0.5f, 0.5f),
		},
		std::vector<glm::vec2> { // water edge
			glm::vec2(0.0f, 0.5f),
			glm::vec2(0.5f, 0.5f),
			glm::vec2(0.5f, 0.0f),
			glm::vec2(0.0f, 0.0f),
		},
		std::vector<glm::vec2> { // bush
			glm::vec2(0.5f, 0.5f),
			glm::vec2(1.0f, 0.5f),
			glm::vec2(1.0f, 0.0f),
			glm::vec2(0.5f, 0.0f),
		},
	};

	short m_Rows = 8;
	short m_Cols = 8;
	short m_TilePixels = 16;
	short m_NumberOfTiles = 64;

	// 64 tiles * 6 vertices * 5 coords (3 position, 2 texture)
	float m_VertexAndTexCoords[1920] = {};

	void Init(const std::string& filePath);
	void CreateTileMap();
};
