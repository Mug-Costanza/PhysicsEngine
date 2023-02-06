#ifndef player_hpp
#define player_hpp

//GLM
#include <GLM/glm/glm.hpp>

// I thought this class would be more useful, but my plans changed.

struct Player
{
	float speed = 3.0f;

	glm::vec3 Position = glm::vec3(4.0f, 0.0f, 3.0f);
};

#endif /* player_hpp */