#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../Rendering/VAO.h"
#include "../Rendering/VBO.h"
#include "../Rendering/ShaderProgram.h"

// ------ Game class exposed - Simple API -
struct Square
{
	float x;
	float y;
	float width;
	float height;

	float zIndex;

	// unsigned int numOfVertices;
	// unsigned int numOfCoordsPerVertex; // total of pos + tex + color + norm
};

struct Sprite
{
	const char* filePath;
	unsigned short textureID;

	unsigned short rows;
	unsigned short cols;
	unsigned short totalSlotsUsed;
	unsigned short defaultSlotToUse = 1;
};

struct OpenGLData // This needs a different name
{
	std::vector<float> vertexData;
	const char* vertexShaderFilePath;
	const char* fragmentShaderFilePath;

	unsigned short textureID;
	unsigned short vaoID;
	unsigned short vboID;
	unsigned short shaderProgramID;

	unsigned int mvpUniformLocation;
	// temp
	glm::mat4 modelMatrix = glm::mat4(1.0f);
};

struct ViewMatrix
{
	glm::mat4 viewMatrix = glm::mat4(1.0f);
};

struct OrthoMatrix
{
    glm::mat4 m_OrthographicProjection = glm::ortho(
       -1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f
    );
};

// ================================== OLD STUFF BELOW ========================

struct ColorRGBA
{
	float r;
	float g;
	float b;
	float a;
};

struct MVPUniform
{
	unsigned int location;
	glm::mat4 mvpMatrix = glm::mat4(1.0f);

};

template <typename T>
using ComponentMap = std::unordered_map<size_t, T>;

using Squares = ComponentMap<Square>;
using Sprites = ComponentMap<Sprite>;
using ColorRGBAs = ComponentMap<ColorRGBA>;
using MVPUniforms = ComponentMap<MVPUniform>;
using OpenGLDatas = ComponentMap<OpenGLData>;

struct Components
{
	Squares squares;
	Sprites sprites;
	ColorRGBAs colorRGBAs;
	MVPUniforms mvpUniforms;
	OpenGLDatas openGLdatas;
};

struct SingleComponents
{
	OrthoMatrix orthoMatrix;
};
