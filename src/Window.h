#pragma once

#include <iostream>
#include <glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();
	~Window();

	int Init(int width, int height);
	GLFWwindow* GetWindow() const { return m_Window; }

private:
	GLFWwindow* m_Window = nullptr;
	int m_Width = 800;
	int m_Height = 600;
};