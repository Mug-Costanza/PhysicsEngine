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

public:
	void AddObject(Object* object);
	void RemoveObject(Object* object);

	int GetNumOfObjects();

	Object *GetObject(int index);

	void AddLight(Light* light);
	void RemoveLight(Light* light);

	void RenderScene();
	void RenderShadows();

	void Update(float dt);

	void Unload();

	glm::vec3 gravity = glm::vec3(0.0f, -1.0f, 0.0f);
};

#endif scene_hpp