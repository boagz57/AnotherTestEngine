#pragma once
#include <GLM/vec3.hpp>

class PositionComponent
{
public:
	inline glm::vec3 GetCurrentState();
	inline void Add(sfloat x, sfloat y);
	
private:
	glm::vec3 worldPosition{ 0.0f, 0.0f, 0.0f };
};

glm::vec3 PositionComponent::GetCurrentState()
{
	return worldPosition;
}

void PositionComponent::Add(sfloat x, sfloat y)
{
	worldPosition.x += x;
	worldPosition.y += y;
}