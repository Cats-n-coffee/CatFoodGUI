#include "VBO.h"

VBO::VBO()
	: m_BufferObjectID(0)
{}

VBO::VBO(unsigned int numOfBuffers)
	: m_BufferObjectID(0)
{
	glGenBuffers(numOfBuffers, &m_BufferObjectID);
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferObjectID);
}

void VBO::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::PassBufferData(unsigned int dataSize, std::vector<float>& data)
{
	glBufferData(GL_ARRAY_BUFFER, dataSize, &data[0], GL_STATIC_DRAW);
}

void VBO::PassBufferData(unsigned int dataSize, float* data)
{
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
}

void VBO::SpecifyDataLayout(unsigned int index, unsigned int size, unsigned int stride, unsigned int offset)
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, (void*)offset);
}
