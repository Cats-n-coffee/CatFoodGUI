#pragma once

#include <string>
#include <unordered_map>
#include <glew.h>

class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(const std::string& vertexFilePath, const std::string& fragmentFilePath);
	~ShaderProgram();

	inline const unsigned int getProgramId() { return m_shaderProgram; }
	void UnBind();
private:
	unsigned int AddShader(const std::string& filePath, GLenum type);

	std::string m_vertexFilePath = "";
	std::string m_fragmentFilePath = "";

	unsigned int m_vertexShader = 0;
	unsigned int m_fragmentShader = 0;

	unsigned int m_shaderProgram = 0;
};