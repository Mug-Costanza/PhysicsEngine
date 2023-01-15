#ifndef object_hpp
#define object_hpp

//std
#include <stdio.h>
#include <vector>

//GLM
#include <GLM/glm/glm.hpp>

//Project Files
#include "physics.hpp"

//Pragma
#pragma once

// PURPOSE : Object class.

class Object // Heap is better than stack.
{
public:
	Object(const char* modelPath);

	const char* modelFile;

	glm::vec3 Position = glm::vec3(0.0f);
	glm::quat Orientation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);
	glm::vec3 Rotation = glm::vec3(0.0f);
	glm::vec3 Scale = glm::vec3(1.0f);

	// Physics variables
	glm::quat angularVelocity;
	glm::vec3 linearVelocity;
	glm::mat3 inverseIntertiaTensors;
	float inverseMass;
	std::vector <glm::vec3> penetrations;

	Collider collider;
	PhysicsType physicsID = RigidBody;
	//RigidBody rigidBody;

	glm::vec3 Velocity = glm::vec3(0.0f);
	float Mass = 1.0f;
	glm::vec3 Force = glm::vec3(0.0f);

	std::vector <glm::vec3> vertices;
	std::vector <glm::vec2> textureCoords;
	std::vector <glm::vec3> normals;

	void render();
	void destroy();

	bool affectedByGravity = true;

private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int normalBuffer;
	unsigned int textureBuffer;

	void initPhysicsBody();
	void initRigidBody();
	void initSoftBody();
	void initLiquidBody();
};

#endif /* object_hpp */