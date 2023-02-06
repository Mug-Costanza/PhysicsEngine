#include "rigidbody.hpp"

void RigidBody::Integrate(float delta)
{
	Position += Velocity * delta;
	collider.Position = this->Position;
}

void RigidBody::SetVelocity(glm::vec3 vel)
{
	Velocity = vel;
}
