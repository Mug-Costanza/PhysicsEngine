#include "scene.hpp"
#include "window/window.hpp"
#include "math/matrices.hpp"

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

int Scene::GetNumOfObjects()
{
	return mObjects.size();
}

Object *Scene::GetObject(int index)
{
	return mObjects[index];
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
		glCullFace(GL_FRONT);

		//for (Object* object : mObjects)
			//object->render();
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
			object->ApplyGravity(dt, gravity);
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