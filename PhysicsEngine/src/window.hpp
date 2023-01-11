#ifndef window_hpp
#define window_hpp

//std
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

//GLEW
#include <GL/glew.h>
#define GLEW_STATIC

//GLFW
#include <GLFW/glfw3.h>

class Window
{
public:
    Window(int windowWidth, int windowHeight, const char *windowTitle);
    
    int getWidth();
    int getHeight();
    std::string getTitle();
    
    GLFWwindow* getWindow();
    
    void run();
    void cleanUp();
    
private:
    int width;
    int height;
    const char *title;
    
    GLFWwindow* window;
};

#endif /* window_hpp */
