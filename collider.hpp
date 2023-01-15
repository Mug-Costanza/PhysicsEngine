#ifndef collider_hpp
#define collider_hpp

//GLM
#include <GLM/glm/glm.hpp>
#include <GLM/glm/gtc/quaternion.hpp>

//Pragma
#pragma once

class Collider
{
public:
	glm::vec3 Position = glm::vec3(0.0f);
	glm::vec3 Rotation = glm::vec3(0.0f);
	glm::vec3 Scale = glm::vec3(1.0f);
	glm::quat Orientation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);
};

#endif /* collider_hpp */