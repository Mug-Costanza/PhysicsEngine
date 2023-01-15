#ifndef window_hpp
#define window_hpp

//std
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

//IMGUI
#include "imgui.h"
#include "imgui_stdlib.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//GLEW
#include <GL/glew.h>
#define GLEW_STATIC

//GLFW
#include <GLFW/glfw3.h>

//Pragma
#pragma once

// PURPOSE : Objects make things look nice and clean, iho. :)

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
