#pragma once

#include <iostream>
#include <glew.h>

class VAO
{
public:
	VAO();
	VAO(unsigned int numOfArrayObjects);

	inline unsigned int GetID() const { return m_ArrayObjectID; }

	void Bind(); // Does this need to take an ID?
	void UnBind(); // If we end up passing an array for multiple VAOs, do we need to update this?
private:
	unsigned int m_ArrayObjectID; // TODO: make this an array, and update logic with indices?
};
