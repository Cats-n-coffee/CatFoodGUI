#pragma once

#include "Application/Application.h"

struct Controller {
    void keyPressEvent()
    {
        std::cout << "event in struct" << std::endl;
    }
};

Controller controller;

// https://gamedev.stackexchange.com/questions/174463/which-is-a-better-way-for-moving-3d-objects-in-opengl



int main()
{
    Application app;
    app.Init();

	return 0;
}