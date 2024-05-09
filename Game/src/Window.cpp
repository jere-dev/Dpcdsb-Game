#include "Window.h"


namespace GE {    

    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    void processInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and 
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }

    Window::Window(int hieght, int width, const char* title, GLFWkeyfun callback)
        : m_hieght(hieght), m_width(width), m_title(title)
    {
        // glfw: initialize and configure
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // glfw window creation
        m_window = glfwCreateWindow(m_width, m_hieght, m_title, NULL, NULL);
        if (m_window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
        }
        glfwMakeContextCurrent(m_window);
        glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

        // glad: load all OpenGL function pointers
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }

        glfwSetKeyCallback(m_window, callback);
        glfwSetWindowAspectRatio(m_window, width, hieght);

    }

    void Window::clear()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::update()
    {
        // input
        processInput(m_window);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }


    Window::~Window()
    {
        glfwTerminate();
        glfwDestroyWindow(m_window);
    }

}