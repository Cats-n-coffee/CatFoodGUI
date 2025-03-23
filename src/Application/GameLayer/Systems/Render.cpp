#include "Render.h"

void SetupCoordsAndColor()
{
}

// Handles squares only for now
void SetupCoordsAndTex(
	ComponentMap<OpenGLData>& openGLDataComponents,
	ComponentMap<Square> squareComponents,
	ComponentMap<Sprite> spriteComponents)
{
	for (const auto& [key, value] : squareComponents)
	{
		// Find the default Sprite slot coords to use
		float spriteCoords[8] = {
			0.0f, 1.0f, // top-left
			0.5f, 1.0f, // top-right
			0.5f, 0.5f, // bottom-right
			0.0f, 0.5f, // bottom-left
		};

		std::cout << "file path " << spriteComponents[key].filePath << std::endl;
		openGLDataComponents[key].textureID = generateTexture2DPNG(spriteComponents[key].filePath);
		std::cout << "assigned " << openGLDataComponents[key].textureID << std::endl;

	    // Fill the openGL vertex data std::vector
		// 6 vertices for a square, 5 coords per vertex (3 pos + 2 tex)
		openGLDataComponents[key].vertexData.resize(6 * 5);
		
		// ------ Top-left - Tri 1
		// Position
		openGLDataComponents[key].vertexData[0] = value.x;
		openGLDataComponents[key].vertexData[1] = value.y;
		openGLDataComponents[key].vertexData[2] = value.zIndex;
		// Texture
		openGLDataComponents[key].vertexData[3] = spriteCoords[0];
		openGLDataComponents[key].vertexData[4] = spriteCoords[1];

		// ------ Top-right - Tri 1
		// Position
		openGLDataComponents[key].vertexData[5] = value.x + value.width;
		openGLDataComponents[key].vertexData[6] = value.y; 
		openGLDataComponents[key].vertexData[7] = value.zIndex;
		// Texture
		openGLDataComponents[key].vertexData[8] = spriteCoords[2];
		openGLDataComponents[key].vertexData[9] = spriteCoords[3];

		// ------- Bottom-left - Tri 1
		// Position
		openGLDataComponents[key].vertexData[10] = value.x;
		openGLDataComponents[key].vertexData[11] = value.y - value.height;
		openGLDataComponents[key].vertexData[12] = value.zIndex;
		// Texture
		openGLDataComponents[key].vertexData[13] = spriteCoords[4];
		openGLDataComponents[key].vertexData[14] = spriteCoords[5];

		// ------- Bottom-left - Tri 2
		// Position
		openGLDataComponents[key].vertexData[15] = value.x;
		openGLDataComponents[key].vertexData[16] = value.y - value.height;
		openGLDataComponents[key].vertexData[17] = value.zIndex;
		// Texture
		openGLDataComponents[key].vertexData[18] = spriteCoords[4];
		openGLDataComponents[key].vertexData[19] = spriteCoords[5];

		// ------ Top-right - Tri 2
		// Position
		openGLDataComponents[key].vertexData[20] = value.x + value.width;
		openGLDataComponents[key].vertexData[21] = value.y; 
		openGLDataComponents[key].vertexData[22] = value.zIndex;
		// Texture
		openGLDataComponents[key].vertexData[23] = spriteCoords[2];
		openGLDataComponents[key].vertexData[24] = spriteCoords[3];

		// ------- Bottom-right - Tri 2
		// Position
		openGLDataComponents[key].vertexData[25] = value.x + value.width;
		openGLDataComponents[key].vertexData[26] = value.y - value.height;
		openGLDataComponents[key].vertexData[27] = value.zIndex;
		// Texture
		openGLDataComponents[key].vertexData[28] = spriteCoords[6];
		openGLDataComponents[key].vertexData[29] = spriteCoords[7];

		// Create OpenGL state and buffers
		openGLDataComponents[key].vaoID = InitVAO();
		BindVAO(openGLDataComponents[key].vaoID);
		openGLDataComponents[key].vboID = InitVBO();
		BindVBO(openGLDataComponents[key].vboID);

		openGLDataComponents[key].shaderProgramID = CreateShaderProgram(
			openGLDataComponents[key].vertexShaderFilePath,
			openGLDataComponents[key].fragmentShaderFilePath
		);
		openGLDataComponents[key].mvpUniformLocation = glGetUniformLocation(
			openGLDataComponents[key].shaderProgramID,
			"modelViewProjection"
		);

		PassVBOData(openGLDataComponents[key].vertexData.size() * sizeof(float), openGLDataComponents[key].vertexData);
		SpecifyDataLayout(0, 3, 5 * sizeof(float), 0); // positions
		SpecifyDataLayout(1, 2, 5 * sizeof(float), 3 * sizeof(float)); // texture

		UnbindVAO();
		UnbindVBO();
		UnbindShaderProgram();
	}
}

void RenderCoordsAndColor()
{
}

void RenderCoordsAndTex(ComponentMap<OpenGLData>& openGLDataComponents, SingleComponents singleComponents)
{
	for (const auto& [key, value] : openGLDataComponents) {
		glBindTexture(GL_TEXTURE_2D, value.textureID);
		glBindVertexArray(value.vaoID);

		glUseProgram(value.shaderProgramID);
		glUniformMatrix4fv(value.mvpUniformLocation, 1, GL_FALSE, &value.modelMatrix[0][0]);

		glDrawArrays(GL_TRIANGLES, 0, (unsigned int)(value.vertexData.size() / 5));
	}
}