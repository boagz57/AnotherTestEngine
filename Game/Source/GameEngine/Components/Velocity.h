#pragma once
#include <GLM/vec3.hpp>

class VelocityComponent
{
public:
	inline glm::vec3 GetCurrentState();
	inline void Add(sfloat x, sfloat y);
	inline void ZeroOut();
	
private:
	glm::vec3 currentVelocity{ 0.0f, 0.0f, 0.0f };
};

glm::vec3 VelocityComponent::GetCurrentState()
{
	return currentVelocity;
}

void VelocityComponent::Add(sfloat x, sfloat y)
{
	this->currentVelocity.x += x;
	this->currentVelocity.y += y;
}

void VelocityComponent::ZeroOut()
{
	currentVelocity *= 0.0f;
}
