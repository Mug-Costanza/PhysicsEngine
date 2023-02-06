#ifndef physics_hpp
#define physics_hpp

//std
#include <assert.h>

//GLM
#include <GLM/glm/glm.hpp>
#include <GLM/glm/gtc/quaternion.hpp>
#include <GLM/glm/common.hpp>

//Project Files
#include "../../scene.hpp"

//Pragma
#pragma once

//enum PhysicsType { RigidBody, SoftBody, LiquidBody };

class PhysicsEngine
{
public:
	PhysicsEngine()
	{
	
	}

	void Simulate(float delta, Scene& scene);

	void HandleCollisions(Scene& scene);
};

#endif /* physics_hpp */