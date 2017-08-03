#pragma once
#include <GLM/vec3.hpp>

class Fighter;

class Velocity
{
public:
	Velocity();
	~Velocity();

private:
	friend class Fighter;
	glm::vec3 velocity{ 0.0f, 0.0f, 0.0f };
};

