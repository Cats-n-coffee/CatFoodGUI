#include "Window.h"

Window::Window()
{
}

int Window::Init(int width, int height)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    m_Window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);

    if (!m_Window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1); // vsync
    glEnable(GL_DEPTH_TEST);

    // GLEW
    glewExperimental = GL_TRUE;

    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        printf("Error with GLEW");
        return -1;
    }

    m_Width = width;
    m_Height = height;

    return 0; // ??
}

void Window::Terminate()
{
    glfwTerminate();
    m_Window = nullptr;
}

Window::~Window()
{
    if (m_Window) delete m_Window;
}
