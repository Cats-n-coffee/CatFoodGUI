#include "Application.h"


namespace Application {
    namespace
    {
        Window m_GameWindow;
        Game m_Game;

		double lastFrame = 0.0;
    }


	void keyEvents(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		m_Game.ProcessKeyEvents(key, scancode, action, mods);
	}

	void framebufferSize(GLFWwindow* window, int width, int height)
	{
		// okay for now, let's see later with a tile map the behavior we want
		// which might be adjusting the camera position closer/further
		// would we also need to pass the window width and height to make it all
		// proportional? (camera and perspective)
		glViewport(0, 0, width, height);
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

		// Window resize
		glfwSetFramebufferSizeCallback(window, framebufferSize);
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
			double currentFrame = glfwGetTime();
			double deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			// First: Update the MVP in shader
			m_Game.Update(deltaTime);

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
