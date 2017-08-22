#include "Transform.h"

glm::vec2 TransformComponent::GetCurrentPosition() const
{
	return position;
}

void TransformComponent::TranslatePosition(sfloat amountToTranslateX, sfloat amountToTranslateY)
{
	position.x += amountToTranslateX;
	position.y += amountToTranslateY;
}

void TransformComponent::MultiplyPosition(int16 const multiplyX, const int16 multiplyY)
{
	position.x *= multiplyX;
	position.y *= multiplyY;
}

void TransformComponent::SetPosition(sfloat locationX, sfloat locationY)
{
	position.x = locationX;
	position.y = locationY;
}