#include "Position.h"

void PositionComponent::MultiplyPositionBy(int16 const c_MultiplyX, int16 const c_MultiplyY)
{
	this->currentPosition.x *= c_MultiplyX;
	this->currentPosition.y *= c_MultiplyY;
}

void PositionComponent::SetPosition(sfloat const positionX, sfloat const positionY)
{
	currentPosition.x = positionX;
	currentPosition.y = positionY;
}

glm::vec2 const PositionComponent::GetCurrentPosition() const
{
	return currentPosition;
}

