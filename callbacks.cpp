#include "callbacks.hpp"

//Key inputs
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == Escape && action == Hold && !glfwWindowShouldClose(window))
    {
        glfwSetWindowShouldClose((window), true);

        std::cout << "The program has shut down" << std::endl;
    }
}

//Character input
void charCallback(GLFWwindow* window, unsigned int keyCode)
{

}

//Character mod input
void charModCallback(GLFWwindow* window, unsigned int keyCode, int modifierKey)
{

}

//Cursor position
void cursorPosCallback(GLFWwindow* window, double xPos, double yPos)
{

}

//Cursor enter
void cursorEnterCallback(GLFWwindow* window, int entered)
{

}

//Mouse buttons
void mButtonCallback(GLFWwindow* window, int mButton, int action, int mods)
{

}

//Mouse scroll
void scrCallback(GLFWwindow* window, double xOffset, double yOffset)
{

}

//Window maximized
void windowMaximizedCallback(GLFWwindow* window, int windowMaximized)
{

}

//Window size
void windowSizeCallback(GLFWwindow* window, int nWidth, int nHeight)
{

}

//Framebuffer size
void frameBufferSizeCallback(GLFWwindow* window, int windowFramebufferWidth, int windowFrameBufferHeight)
{

}
