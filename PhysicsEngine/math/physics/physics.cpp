#include "physics.hpp"

void PhysicsEngine::Simulate(float delta, Scene &scene)
{
	for (unsigned int i = 0; i < scene.GetNumOfObjects(); i++)
	{
		scene.GetObject(i)->rigidBody.Integrate(delta);
	}
}

void PhysicsEngine::HandleCollisions(Scene &scene)
{
	for (int i = 0; i < scene.GetNumOfObjects(); i++)
	{
		for (int j = 0; j < scene.GetNumOfObjects(); j++)
		{
			// This is really terrible, I'm so sorry.
			switch (scene.GetObject(i)->rigidBodyType)
			{
			case(BoxBody):

				switch (scene.GetObject(j)->rigidBodyType)
				{
				case(BoxBody):

					break;

				case(SphereBody):

					break;

				case(PlaneBody):

					break;
				}

				break;

			case(SphereBody):

				switch (scene.GetObject(j)->rigidBodyType)
				{
				case(BoxBody):

					//CollisionData collisionData = scene.GetObject(i)->GetBoundingSphere().CollisionBoundingBox(scene.GetObject(i)->GetBoundingBox());

					//if (collisionData.getDoesCollide())
					//{
						//scene.GetObject(i)->rigidBody.SetVelocity(scene.GetObject(i)->Velocity * glm::vec3(-1.0f));
						//scene.GetObject(j)->rigidBody.SetVelocity(scene.GetObject(j)->Velocity * glm::vec3(-1.0f));
					//}

					break;

				case(SphereBody):

					//CollisionData collisionData = scene.GetObject(i)->GetBoundingSphere().CollisionBoundingSphere(scene.GetObject(i)->GetBoundingSphere());

					//if (collisionData.getDoesCollide())
					//{
						//scene.GetObject(i)->rigidBody.SetVelocity(scene.GetObject(i)->Velocity * glm::vec3(-1.0f));
						//scene.GetObject(j)->rigidBody.SetVelocity(scene.GetObject(j)->Velocity * glm::vec3(-1.0f));
					//}

					break;

				case(PlaneBody):

					break;
				}

				break;

			case(PlaneBody):

				switch (scene.GetObject(j)->rigidBodyType)
				{
				case(BoxBody):

					break;

				case(SphereBody):

					break;

				case(PlaneBody):

					break;
				}

				break;
			}
		}
	}
}
