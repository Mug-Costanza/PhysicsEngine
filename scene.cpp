#include "scene.hpp"
#include "window.hpp"
#include "matrices.hpp"

extern Window window;
extern unsigned int shaderID, depthShaderID;

void Scene::AddObject(Object* object)
{
	if (object == nullptr)
		return;

	mObjects.push_back(object);
}

void Scene::RemoveObject(Object* object)
{
	if (!object)
		return;

	for (Object* object : mObjects)
		object->destroy();

	auto itr = std::find(mObjects.begin(), mObjects.end(), object);

	if (itr == mObjects.end())
		return;

	mObjects.erase(itr);
}

void Scene::AddLight(Light* light)
{
	if (light == nullptr)
		return;

	mLights.push_back(light);
}

void Scene::RemoveLight(Light* light)
{
	if (!light)
		return;

	auto itr = std::find(mLights.begin(), mLights.end(), light);

	if (itr == mLights.end())
		return;

	mLights.erase(itr);
}

void Scene::RenderShadows()
{
	for (Light* light : mLights)
	{
		light->render(); // Applies uniform variables to the shader.

		// Render framebuffer texture
		glUseProgram(depthShaderID);
		glViewport(0, 0, light->getShadowWidth(), light->getShadowHeight());
		glBindFramebuffer(GL_FRAMEBUFFER, light->getDepthMapBuffer());
		glClear(GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, light->getDepthMap());
		glCullFace(GL_FRONT);

		for (Object* object : mObjects)
			object->render();
	}

	// Reset framebuffer, viewport, and screen
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, int(window.getWidth()), int(window.getHeight()));
	glUseProgram(shaderID);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glCullFace(GL_BACK);
}

void Scene::RenderScene()
{
	for (Light* light : mLights)
	{
		//light->render();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, light->getDepthMap());

		for (Object* object : mObjects)
			object->render();
	}
}

void Scene::Update(float dt)
{
	for (Object* object : mObjects)
	{
		if (object->affectedByGravity)
		{
			//object->Force += object->Mass * gravity;
			//object->Velocity += object->Force / object->Mass * dt;
			//object->Position += object->Velocity * dt;
			//object->Force = glm::vec3(0.0f);
		}
	}

	ResolveCollisions(dt);
}

void Scene::ResolveCollisions(float dt)
{
	for (Object* objA : mObjects)
	{
		for (Object* objB : mObjects)
		{
			if (objA == objB)
				break;

			if (!objA || !objB)
				break;


		}
	}
}

void Scene::CalculateCollisions()
{
	for (Object* object : mObjects)
	{
		glm::mat4 objectModelMat = CheckMatrices(*object);

		for (int i = 0; i < object->vertices.size() / sizeof(glm::vec3); i++)
		{
			glm::vec3 transformedPoint = glm::vec3(objectModelMat * glm::vec4(object->vertices[i], 1));

			for (Object* object : mObjects)
			{
				for (Object* object2 : mObjects)
				{
					glm::vec3 collisionNormal = glm::vec3(glm::mat4_cast(object->Orientation) * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
					float collisionOffset = glm::dot(object->Position, collisionNormal);
					float vertexDistance = glm::dot(transformedPoint, collisionNormal);

					if (vertexDistance < collisionOffset)
					{
						numContacts++;

						contactPoints[numContacts - 1].contactNormal = collisionNormal;
						contactPoints[numContacts - 1].contactPosition = collisionNormal * glm::abs(vertexDistance - collisionOffset) / 2.0f + transformedPoint;
						contactPoints[numContacts - 1].penetrationDepth = collisionOffset - vertexDistance;
						contactPoints[numContacts - 1].rb1 = object;
						contactPoints[numContacts - 1].rb2 = object2;

						glm::quat& angVelQ = object->angularVelocity;
						glm::vec3 angVel = glm::vec3(angVelQ.x, angVelQ.y, angVelQ.z);

						contactPoints[numContacts - 1].closingVelocity = glm::cross(angVel, contactPoints[numContacts - 1].contactPosition - object->Position) + object->linearVelocity;
					}
				}
			}
		}
	}
}

void Scene::ResolveCollisions(float dt)
{
	for (int i = 0; i < numContacts; i++)
	{
		CollisionPointRB& p = contactPoints[i];

		glm::vec3 closingVelocity = glm::dot(p.closingVelocity, p.contactNormal) * p.contactNormal;
		glm::vec3 desiredVelocity = (-closingVelocity * (1 + restitution));

		glm::vec3 relPoint = p.contactPosition - p.rb1->Position;
		glm::vec3 torquePerUnit = glm::cross(relPoint, p.contactNormal);
		glm::mat3 rotationMat = glm::mat3_cast(p.rb1->Orientation);
		glm::vec3 angVelPerUnit = rotationMat * torquePerUnit;
		angVelPerUnit = p.rb1->inverseIntertiaTensors * angVelPerUnit;
		angVelPerUnit = glm::inverse(rotationMat) * angVelPerUnit;
		glm::vec3 linearVelPerUnit = glm::cross(angVelPerUnit, relPoint);

		float linFromAngPerUnitImpulse = glm::dot(linearVelPerUnit, p.contactNormal);
		float velPerUnitImpulse = p.rb1->inverseMass + linFromAngPerUnitImpulse;

		glm::vec3 impulse = desiredVelocity / velPerUnitImpulse;

		glm::vec3 impulsiveTorque = glm::cross(relPoint, impulse);
		glm::vec3 rotationChange = rotationMat * impulsiveTorque;
		rotationChange = p.rb1->inverseIntertiaTensors * rotationChange;
		rotationChange = glm::inverse(rotationMat) * rotationChange;
		p.rb1->angularVelocity += glm::quat(0, rotationChange.x, rotationChange.y, rotationChange.z);

		glm::vec3 linearImpulse = p.rb1->inverseMass * impulse;
		p.rb1->linearVelocity += linearImpulse;
	}
}

void Scene::ApplyForces(float dt)
{
	for (Object* object : mObjects)
	{
		object->linearVelocity * dampening + gravity * dt;
		object->angularVelocity *= dampening;
	}
}

void Scene::applyRigidBodyPhysics(float dt)
{
	glm::vec3 angularVelocity = glm::vec3(0.0f);

	numContacts = 0;

	penetrations.clear();

	for (Object* object : mObjects)
	{
		penetrations.push_back(glm::vec3(0.0f));

		if (object->inverseMass != -1.0f)
		{
			ApplyForces(dt);

			CalculateCollisions();
		}
	}

	ResolveCollisions(dt);

	ResolveInterpenetration(dt);

	for (Object* object : mObjects)
	{
		if (object->inverseMass != -1.0f)
		{
			object->Position += object->linearVelocity * dt;
			object->Orientation = glm::normalize(object->Orientation + dt / 2.0f * object->angularVelocity * object->Orientation);
		}
	}
}

void Scene::Unload()
{
	for (Object* object : mObjects)
		RemoveObject(object);

	for (Light* light : mLights)
		RemoveLight(light);
}