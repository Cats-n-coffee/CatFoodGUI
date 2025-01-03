#include "Application.h"


namespace Application {
    namespace
    {
        Window m_GameWindow;
        Game m_Game;
    }


	void keyEvents(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		m_Game.ProcessKeyEvents(key, scancode, action, mods);
	}

	void Init()
	{
		// Init window
		m_GameWindow.Init(800, 600);
		GLFWwindow* window = m_GameWindow.GetWindow();

		// Init game
		m_Game.Init();

		// User input
		glfwSetKeyCallback(window, keyEvents);

		/*
		while(Game.IsRunning)
		{
			Input = GetInput();
			Game.Update(Input);
			Display(Game);
		}
		*/
	}

	void Run()
	{
		GLFWwindow* window = m_GameWindow.GetWindow();

		while (!glfwWindowShouldClose(window))
		{

			// First: Update the MVP in shader
			m_Game.Update();

			// Second: Render
			m_Game.Render();

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

		m_GameWindow.Terminate();
	}
}
