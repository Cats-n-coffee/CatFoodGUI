#pragma once


#include <iostream>
#include <vector>
#include <string>
#include <glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "Window.h"
#include "GameLayer/Game.h"
#include "GameLayer/Rendering/ShaderProgram.h"
#include "GameLayer/GameObjects/Cat.h"


namespace Application
{

	void keyEvents(GLFWwindow* window, int key, int scancode, int action, int mods);
	void framebufferSize(GLFWwindow* window, int width, int height);

	void Init();
	void Run();
}
