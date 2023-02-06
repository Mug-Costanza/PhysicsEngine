#include "collider.hpp"

float MaxFunction(glm::vec3& vec)
{
	float result = vec[0];

	for (int i = 0; i < sizeof(glm::vec3); i++)
	{
		if (vec[i] > result)
			result = vec[i];
	}

	std::cout << "Result : " << result << std::endl;

	return result;
}

glm::vec3 MaxFunction2(glm::vec3& vec, glm::vec3& vec2)
{
	glm::vec3 result;

	for (int i = 0; i < sizeof(glm::vec3); i++)
	{
		result[i] = vec[i] > vec2[i] ? vec[i] : vec2[i];
	}

	return result;
}

void Collider::MoveCollider(glm::vec3 inPos)
{
	this->Position = inPos;

	switch (this->type)
	{
	case(BOX_COLLIDER):


			break;
	case(PLANE_COLLIDER):
		

		break;
	case(SPHERE_COLLIDER):
		  

		break;
	}
}

CollisionData Collider::Collision(const Collider& other) const
{
	if (type == SPHERE_COLLIDER && other.GetType() == SPHERE_COLLIDER)
	{
		BoundingSphere* self = (BoundingSphere*)this;
		return self->CollisionBoundingSphere((BoundingSphere&)other);
	}

	exit(1);

	return CollisionData(false, 0);
}

CollisionData BoundingBox::CollisionBoundingBox(const BoundingBox& box) const
{
	glm::vec3 distance1 = box.GetMinExtents() - maxExtents;
	glm::vec3 distance2 = minExtents - box.GetMaxExtents();
	glm::vec3 distances = glm::vec3(MaxFunction2(distance1, distance2));

	float maxDistance = MaxFunction(distances);

	return CollisionData(maxDistance < 0, maxDistance);
}

BoundingPlane BoundingPlane::Normalized() const
{
	float maginitude = normal.length();

	return BoundingPlane(normal / maginitude, distance / maginitude);
}

CollisionData BoundingPlane::CollisionBoundingSphere(const BoundingSphere& sphere) const
{
	float distanceFromSphereCenter = glm::abs(glm::dot(normal, sphere.GetCenter()) + distance);
	float distanceFromSphere = distanceFromSphereCenter - sphere.GetRadius();

	return CollisionData(distanceFromSphere < 0, distanceFromSphere);
}

CollisionData BoundingSphere::CollisionBoundingSphere(const BoundingSphere& sphere)
{
	float radiusDistance = radius + sphere.radius;
	float centerDistance = (sphere.GetCenter() - center).length();
	float distance = centerDistance - radiusDistance;

	return CollisionData(centerDistance < radiusDistance, distance);
}
