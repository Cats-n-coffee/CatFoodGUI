#include "VAO_v2.h"

unsigned int InitVAO()
{
	unsigned int vaoID = 0;
	glGenVertexArrays(1, &vaoID);

	return vaoID;
}

void BindVAO(unsigned int vaoID)
{
	if (!vaoID) return; // TODO: how to handle?

	glBindVertexArray(vaoID);
}

void UnbindVAO()
{
	glBindVertexArray(0);
}
