#include "Transform.h"

TransformComponent::TransformComponent(glm::vec2 position) :
	Component(0),
	position(position)
{}

void TransformComponent::TranslatePosition(sfloat amountToTranslateX, sfloat amountToTranslateY)
{
	position.x += amountToTranslateX;
	position.y += amountToTranslateY;
}

glm::vec2 TransformComponent::GetCurrentPosition()
{
	return position;
}

void TransformComponent::SetPosition(sfloat locationX, sfloat locationY)
{
	position.x = locationX;
	position.y = locationY;
}