#ifndef scene_hpp
#define scene_hpp

//std
#include <vector>

//GLM
#include <GLM/glm/glm.hpp>

//Project files
#include "object.hpp"
#include "light.hpp"

//Pragma
#pragma once

class Scene
{
private:
	std::vector <Object*> mObjects;
	std::vector <Light*> mLights;

	glm::vec3 gravity = glm::vec3(0.0f, -1.0f, 0.0f);

	// Physics functions
	void CalculateCollisions();
	void ApplyForces(float dt);
	void applyRigidBodyPhysics(float dt);
	void ResolveCollisions(float dt);
	void ResolveInterpenetration(float dt);

	std::vector <glm::vec3> penetrations;

	const static int maxNumCollisions = 10000;
	int numContacts;
	CollisionPointRB contactPoints[4000];
	CollisionPointRB resolvePenetrationsPoints[1000];

	float restitution = 0.1f;
	float dampening = 0.99f;

public:
	void AddObject(Object* object);
	void RemoveObject(Object* object);

	void AddLight(Light* light);
	void RemoveLight(Light* light);

	void RenderScene();
	void RenderShadows();

	void Update(float dt);

	void Unload();
};

#endif scene_hpp