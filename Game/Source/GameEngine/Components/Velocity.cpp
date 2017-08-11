#include "Velocity.h"

VelocityComponent::VelocityComponent() :
	Component(1)
{}

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