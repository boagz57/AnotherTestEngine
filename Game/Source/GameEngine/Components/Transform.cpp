#include "Transform.h"

glm::vec2 const TransformComponent::GetCurrentTranslation() const
{
	return translation;
}

void TransformComponent::Translate(sfloat amountToTranslateX, sfloat amountToTranslateY)
{
	translation.x += amountToTranslateX;
	translation.y += amountToTranslateY;
}