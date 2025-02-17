#pragma once

#include <vector>
#include <glew.h>

class VBO
{
public:
	VBO();
	VBO(unsigned int numOfBuffers);

	void Bind();
	void UnBind();

	void PassBufferData(unsigned int dataSize, std::vector<float>& data);
	void PassBufferData(unsigned int dataSize, float* data);

	void SpecifyDataLayout(unsigned int index, unsigned int size, unsigned int stride, unsigned int offset);
private:
	unsigned int m_BufferObjectID;
	// TODO: handle the type of buffers: VBO or IBO, or a diff class?
};
