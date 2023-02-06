#ifndef object_hpp
#define object_hpp

//std
#include <stdio.h>
#include <vector>

//GLM
#include <GLM/glm/glm.hpp>
#include <GLM/glm/gtc/quaternion.hpp>
#include <GLM/glm/common.hpp>

//Project Files
#include "math/physics/rigidbody.hpp"

//Pragma
#pragma once

// PURPOSE : Object class.

enum PhysicsID { BOX, SPHERE, PLANE, NULLBODY };

class Object
{
public:
	explicit Object(const char* modelPath, PhysicsID in);

	const char* modelFile;

	glm::vec3 Position = glm::vec3(0.0f);
	glm::quat Orientation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);
	glm::vec3 Rotation = glm::vec3(0.0f);
	glm::vec3 Scale = glm::vec3(1.0f);

	glm::vec3 Velocity = glm::vec3(0.0f);
	float Mass = 1.0f;
	glm::vec3 Force = glm::vec3(0.0f);

	//Collider collider;
	//PhysicsType physicsID = RigidBody;
	RigidBody rigidBody;
	RigidBodyType rigidBodyType = BoxBody;

	std::vector <glm::vec3> vertices;
	std::vector <glm::vec2> textureCoords;
	std::vector <glm::vec3> normals;

	void render();
	void destroy();

	bool affectedByGravity = true;

	void ApplyGravity(float dt, glm::vec3 gravity);

private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int normalBuffer;
	unsigned int textureBuffer;

	int physicsID;

	void InitPhysicsBody();

	const glm::vec3& minExtents = glm::vec3(0.0f);
	const glm::vec3& maxExtents = glm::vec3(0.0f);
};

#endif /* object_hpp */