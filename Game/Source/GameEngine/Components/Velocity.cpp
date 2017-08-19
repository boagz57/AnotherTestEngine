#include "Velocity.h"

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