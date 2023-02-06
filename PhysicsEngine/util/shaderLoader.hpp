#ifndef shaderLoader_hpp
#define shaderLoader_hpp

//std
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

//GLEW
#include <GL/glew.h>
#define GLEW_STATIC

//GLFW
#include <GLFW/glfw3.h>

//GLM
#include <GLM/glm/glm.hpp>

//Pragma
#pragma once

// PURPOSE : Orginization, I guess.

class Shader
{
public:
	unsigned int shaderID;

	const char* pathID;

	std::string ID;
};

// PURPOSE : Uses OpenGL to load and read shader files. Shader files pass instructions on the GPU.

unsigned int LoadShader(const char* vPath, const char* fPath);

#endif /* shaderLoader_hpp */