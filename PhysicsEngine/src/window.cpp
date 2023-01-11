#include "window.hpp"

Window::Window(int windowWidth, int windowHeight, const char *windowTitle) : width(windowWidth), height(windowHeight), title(windowTitle)
{
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
}

void Window::run()
{
    glClear( GL_COLOR_BUFFER_BIT );
}

void Window::cleanUp()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

int Window::getWidth()
{
    return width;
}

int Window::getHeight()
{
    return height;
}

std::string Window::getTitle()
{
    return title;
}

GLFWwindow* Window::getWindow()
{
    return window;
}

/*
 Ignoring file /Users/zacharybunch/Desktop/PhysicsEngine/PhysicsEngine/OpenGL-Root/libs/libGLEW.2.2.0.dylib, building for macOS-x86_64 but attempting to link with file built for macOS-arm64

 */
