#ifndef objLoader_hpp
#define objLoader_hpp

//std
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

//GLEW
#include <GL/glew.h>
#define GLEW_STATIC

//GLFW
#include <GLFW/glfw3.h>

//GLM
#include <GLM/glm/glm.hpp>
#include <GLM/glm/gtc/matrix_transform.hpp>
#include <GLM/glm/gtc/type_ptr.hpp>
#include <GLM/glm/gtx/transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <GLM/glm/gtx/string_cast.hpp>

//Pragma
#pragma warning(disable:4996)

// Purpose : Loads and compiles OBJ files.
// Can only import models with triangles rather than quads, requires UV, requires normals, keep vertex order is always good.
bool LoadOBJ(const char* modelPath, std::vector <glm::vec3>& outVertices, std::vector <glm::vec2>& outTextureCoords, std::vector <glm::vec3>& outNormals);

#endif /* objLoader_hpp */