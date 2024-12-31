#include "VAO.h"

VAO::VAO()
	: m_ArrayObjectID(0)
{}

VAO::VAO(unsigned int numOfArrayObjects)
	: m_ArrayObjectID(0)
{
	if (numOfArrayObjects > 1) std::cout << "Generation of more than 1 VAO unsupported" << '\n';
	glGenVertexArrays(numOfArrayObjects, &m_ArrayObjectID);
}

void VAO::Bind()
{
	glBindVertexArray(m_ArrayObjectID);
}

void VAO::UnBind()
{
	glBindVertexArray(0);
}