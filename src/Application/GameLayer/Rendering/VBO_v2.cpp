#include "VBO_v2.h"

unsigned int InitVBO()
{
	unsigned int vboID = 0;
	glGenBuffers(1, &vboID);

	return vboID;
}

void BindVBO(unsigned int vboID)
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
}

void UnbindVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PassVBOData(unsigned int dataSize, std::vector<float>& data)
{
	glBufferData(GL_ARRAY_BUFFER, dataSize, &data[0], GL_STATIC_DRAW);
}

void PassVBOData(unsigned int dataSize, float* data)
{
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
}

void SpecifyDataLayout(unsigned int index, unsigned int size, unsigned int stride, unsigned int offset)
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (void*)offset);
}
