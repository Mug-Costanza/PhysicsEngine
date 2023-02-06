#ifndef collider_hpp
#define collider_hpp

//std
#include <stdio.h>
#include <iostream>
#include <vector>

//GLM
#include <GLM/glm/glm.hpp>
#include <GLM/glm/gtc/quaternion.hpp>

//Pragma
#pragma once

class CollisionData
{
public:
	CollisionData(const bool inDoesCollide, const float inDistance) : doesCollide(inDoesCollide), distance(inDistance)
	{
		
	}

	inline bool getDoesCollide() const 
	{
		return doesCollide;
	}

	inline float getDistance() const
	{
		return distance;
	}

private:
	const bool doesCollide;
	const float distance;

};

class BoundingBox;
class BoundingSphere;

class Collider
{
public:
	glm::vec3 Position = glm::vec3(0.0f);
	glm::vec3 Rotation = glm::vec3(0.0f);
	glm::vec3 Scale = glm::vec3(1.0f);
	glm::quat Orientation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);

	enum 
	{
		BOX_COLLIDER,
		SPHERE_COLLIDER,
		PLANE_COLLIDER,
	};

	Collider(int inType) : type(inType)
	{

	}

	CollisionData Collision(const Collider& other) const;

	void MoveCollider(glm::vec3 inPos);

	inline int GetType() const 
	{
		return type;
	}

private:
	int type;
};

class BoundingBox : public Collider
{
public:
	BoundingBox(const glm::vec3& inMinExtents, const glm::vec3& inMaxExtents) : Collider(Collider::BOX_COLLIDER), minExtents(inMinExtents), maxExtents(inMaxExtents)
	{

	}

	CollisionData CollisionBoundingBox(const BoundingBox& box) const;

	const glm::vec3 GetMinExtents() const
	{
		return minExtents;
	}

	const glm::vec3 GetMaxExtents() const
	{
		return maxExtents;
	}

private:
	const glm::vec3 minExtents;
	const glm::vec3 maxExtents;
};

class BoundingPlane : public Collider
{
public:
	BoundingPlane(const glm::vec3& inNormal, const float& inDistance) : Collider(Collider::PLANE_COLLIDER), normal(inNormal), distance(inDistance)
	{

	}

	BoundingPlane Normalized() const;

	CollisionData CollisionBoundingSphere(const BoundingSphere& sphere) const;

	const glm::vec3 GetNormal() const
	{
		return normal;
	}

	const float GetDistance() const
	{
		return distance;
	}
	
private:
	const glm::vec3 normal;
	const float distance;
};

class BoundingSphere : public Collider
{
public:
	BoundingSphere(const glm::vec3& inCenter, float inRadius) : Collider(SPHERE_COLLIDER), center(inCenter), radius(inRadius)
	{
		
	}

	CollisionData CollisionBoundingSphere(const BoundingSphere& sphere);

	inline const glm::vec3 GetCenter() const
	{
		return center;
	}

	inline const float GetRadius() const
	{
		return radius;
	}

private:
	const glm::vec3 center;
	float radius;
};

#endif /* collider_hpp */