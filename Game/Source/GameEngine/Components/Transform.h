#pragma once
#include <GLM/vec2.hpp>

class TransformComponent
{
public:
	inline void TranslatePosition(sfloat amountToTranslateX, sfloat amountToTranslateY);
	inline glm::vec2 GetCurrentTranslationAmount();
	inline void ResetTranslation();

private:
	glm::vec2 currentTranslation{ 0.0f, 0.0f };
};

void TransformComponent::TranslatePosition(sfloat amountToTranslateX, sfloat amountToTranslateY)
{
	currentTranslation.x += amountToTranslateX;
	currentTranslation.y += amountToTranslateY;
}

glm::vec2 TransformComponent::GetCurrentTranslationAmount()
{
	return currentTranslation;
}

void TransformComponent::ResetTranslation()
{
	currentTranslation *= 0.0f;
}