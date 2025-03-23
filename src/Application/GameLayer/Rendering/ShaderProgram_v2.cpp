#include "ShaderProgram_v2.h"

unsigned int CreateShaderProgram(const std::string& vertexFilePath, const std::string& fragmentFilePath)
{
	// Create program
	unsigned int programId = glCreateProgram();

	AddShaderToProgram(programId, vertexFilePath, GL_VERTEX_SHADER);
	AddShaderToProgram(programId, fragmentFilePath, GL_FRAGMENT_SHADER);

	glLinkProgram(programId);
	glUseProgram(programId);

	// TODO: move the attrib location bind to its own function?
	// ensures the "(location = 0)" gets bound to its "position" name
	glBindAttribLocation(programId, 0, "aPosition");
	glBindAttribLocation(programId, 1, "aTexCoord");

	return programId;
}

// TODO: make this static?
unsigned int AddShaderToProgram(unsigned int programId, const std::string& filePath, GLenum type)
{
	// Parse shader file to string
	std::string shaderFileContent = ReadResourceFileToStr(filePath);
	const char* shaderCodePtr = shaderFileContent.c_str();

	// Create, assign and compile
	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &shaderCodePtr, NULL);
	glCompileShader(shader);

	glAttachShader(programId, shader);

	return shader;
}

void UnbindShaderProgram()
{
	glUseProgram(0);
}
