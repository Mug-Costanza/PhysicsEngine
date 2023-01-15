#ifndef physics_hpp
#define physics_hpp

//std
#include <assert.h>

//GLM
#include <GLM/glm/glm.hpp>
#include <GLM/glm/gtc/quaternion.hpp>
#include <GLM/glm/common.hpp>

//Project Files
#include "collider.hpp"

//Pragma
#pragma once

extern class Object;

enum PhysicsType { RigidBody, SoftBody, LiquidBody };

struct CollisionPointRB
{
	Object* rb1;
	Object* rb2;

	glm::vec3 closingVelocity;
	glm::vec3 contactPosition;
	glm::vec3 contactNormal;
	glm::vec3 desiredVelocityChange;
	float penetrationDepth;
};

struct RigidBody
{
	
};

#endif /* physics_hpp */