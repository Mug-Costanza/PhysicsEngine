#ifndef rigidbody_hpp
#define rigidbody_hpp

//GLM
#include <GLM/glm/glm.hpp>
#include <GLM/glm/gtc/quaternion.hpp>
#include <GLM/glm/common.hpp>

//Project Files
#include "../collider.hpp"

enum RigidBodyType { BoxBody, SphereBody, PlaneBody };

class RigidBody
{
public:
	RigidBody()
	{

	}

	RigidBody(const glm::vec3& inPos, const glm::vec3& inVelocity) : Position(inPos), Velocity(inVelocity)
	{

	}
	
	void InitRigidBody(glm::vec3 inPos, const glm::vec3& inVelocity)
	{
		this->Position = inPos;
		this->Velocity = inVelocity;
	}

	// Updates rigidbody position; called by the physics engine
	void Integrate(float delta);

	glm::vec3 Position;
	glm::vec3 Velocity;

	// Update velocity according to input
	void SetVelocity(glm::vec3 vel);

	Collider collider = Collider(Collider::SPHERE_COLLIDER);
};

#endif /* rigidbody_hpp */