#include "Velocity.h"

glm::vec2 const VelocityComponent::GetCurrentState() const
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