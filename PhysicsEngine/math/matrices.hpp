#ifndef matrices_hpp
#define matrices_hpp

//std
#include <stdio.h>
#include <iostream>

//GLEW
#include <GL/glew.h>
#define GLEW_STATIC

//GLFW
#include <GLFW/glfw3.h>

//GLM
#define GLM_ENABLE_EXPERIMENTAL
#include <GLM/glm/gtx/string_cast.hpp>

//Project Files
#include "../object.hpp"
#include "collider.hpp"

//Pragma
#pragma once

// PURPOSE : Functions that make translations easier to call.

// Translation function
glm::mat4 Translate(glm::vec3 transCoords);

// Rotation functions
glm::mat4 Rotate(glm::vec3 rotCoords);

// Scaling function
glm::mat4 Scale(glm::vec3 scaleCoords);

// Return the value to the model matrix
glm::mat4 CheckMatrices(Object &object);

// Return the value to the model matrix
glm::mat4 CheckMatrices_Collider(Collider &collider);

#endif /* matrices_hpp */
