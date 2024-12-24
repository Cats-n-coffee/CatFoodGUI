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
#include "../gameLayer/Game.h"
#include "../ShaderProgram.h"
#include "../gameObjects/Cat.h"


static void keyEvents(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::cout << "Key events function" << std::endl;
//    controller.keyPressEvent();
//    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) // TODO: need viewport bounds
//    {
//        if (playerDirection != 3)
//        {
//            rotateDegrees = 270.0f;
//            playerDirection = 3;
//        }
//        translateRect.x += 0.1f;
//        std::cout << "prssed " << translateRect.x << std::endl;
//    }
//    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) // need viewport bounds
//    {
//        if (playerDirection != 1)
//        {
//            rotateDegrees = 90.0f;
//            playerDirection = 1;
//        }
//        translateRect.x -= 0.1f;
//        std::cout << "prssed " << translateRect.x << std::endl;
//    }
//    if (key == GLFW_KEY_UP && action == GLFW_PRESS) // need viewport bounds
//    {
//        if (playerDirection != 2)
//        {
//            rotateDegrees = 180.0f;
//            playerDirection = 2;
//        }
//        translateRect.y += 0.1f;
//    }
//    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) // TODO: viewport bounds
//    {
//        if (playerDirection != 0)
//        {
//            rotateDegrees = 0.0f;
//            playerDirection = 0;
//        }
//        translateRect.y -= 0.1f;
//    }
}
// TODO: re-evaluate if this needs to be a class
// So far we don't have members, so none being initialized
// and nothing private.
// Should this be a struct or can it stay class
// Maybe a class because the lifetime of the object
class Application
{
public:
	Application();
	~Application();

	void Init();


	glm::vec3 translateRect = glm::vec3(0.0f, 0.0f, 0.0f);
	float rotateDegrees = 0.0f;

	short playerDirection = 0;
private:
};
