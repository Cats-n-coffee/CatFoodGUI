#pragma once

#include <vector>
#include <glew.h>

unsigned int InitVBO();

void BindVBO(unsigned int vboID);
void UnbindVBO();

void PassVBOData(unsigned int dataSize, std::vector<float>& data);
void PassVBOData(unsigned int dataSize, float* data);

void SpecifyDataLayout(unsigned int index, unsigned int size, unsigned int stride, unsigned int offset);
