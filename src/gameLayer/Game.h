#pragma once

#include <iostream>
#include <GLFW/glfw3.h>

class Game
{
public:
	// TODO: do we need a constructor?
	// the whole point of one is to destroy it when needed
	void Init();

	void Update();
	void Render();

private:

};