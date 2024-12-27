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
	void Terminate();

	GLFWwindow* GetWindow() const { return m_Window; }
	int GetWindowWidth() const { return m_Width; }
	int GetWindowHeight() const { return m_Height; }

private:
	GLFWwindow* m_Window = nullptr;
	int m_Width = 800;
	int m_Height = 600;
};