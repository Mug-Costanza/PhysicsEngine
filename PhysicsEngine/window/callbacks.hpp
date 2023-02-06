#ifndef callbacks_hpp
#define callbacks_hpp

//std
#include <stdio.h>
#include <iostream>
#include <string>

//GLEW
#include <GL/glew.h>
#define GLEW_STATIC

//GLFW
#include <GLFW/glfw3.h>

//Project headers
#include "keyCode.h"

//Pragma
#pragma once

// PURPOSE : Defines functions for various GLFW window calls.

//Key inputs
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

//Character input
void charCallback(GLFWwindow* window, unsigned int keyCode);

//Character mod input
void charModCallback(GLFWwindow* window, unsigned int keyCode, int modifierKey);

//Cursor position
void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);

//Cursor enter
void cursorEnterCallback(GLFWwindow* window, int entered);

//Mouse buttons
void mButtonCallback(GLFWwindow* window, int mButton, int action, int mods);

//Mouse scroll
void scrCallback(GLFWwindow* window, double xOffset, double yOffset);

//Window maximized
void windowMaximizedCallback(GLFWwindow* window, int windowMaximized);

//Window size
void windowSizeCallback(GLFWwindow* window, int nWidth, int nHeight);

//Framebuffer size
void frameBufferSizeCallback(GLFWwindow* window, int windowFramebufferWidth, int windowFrameBufferHeight);

#endif /* callbacks_hpp */
