#pragma once

#include <iostream>

#include "../Rendering/VAO_v2.h"
#include "../Rendering/VBO_v2.h"
#include "../Rendering/ShaderProgram_v2.h"

#include "../Components/Components.h"

#include "../../../resourceProcessing/Texture2DPNG.h"

void SetupCoordsAndColor();

void SetupCoordsAndTex(
	ComponentMap<OpenGLData>& openGLDataComponents,
	ComponentMap<Square> squareComponents,
	ComponentMap<Sprite> spriteComponents);

void RenderCoordsAndColor();

void RenderCoordsAndTex(ComponentMap<OpenGLData>& openGLDataComponents, SingleComponents singleComponents);
