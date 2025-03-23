#pragma once

#include <string>
#include <glew.h>

#include "../../../resourceProcessing/FileParser.h"

unsigned int CreateShaderProgram(const std::string& vertexFilePath, const std::string& fragmentFilePath);

unsigned int AddShaderToProgram(unsigned int programId, const std::string& filePath, GLenum type);

void UnbindShaderProgram();
