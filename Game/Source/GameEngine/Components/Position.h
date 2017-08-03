#pragma once
#include <GLM/vec3.hpp>

class Fighter;

class Position
{
public:
	Position();
	~Position();
	
private:
	friend class Fighter;
	glm::vec3 worldPosition{ 0.0f, 0.0f, 0.0f };
};