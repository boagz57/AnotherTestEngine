#pragma once
#include <GLM/vec2.hpp>

class TransformComponent
{
public:
	inline void TranslatePosition(sfloat amountToTranslateX, sfloat amountToTranslateY);
	inline glm::vec2 GetCurrentPosition();
	inline void SetPosition(sfloat locationX, sfloat locationY);

private:
	glm::vec2 position{ 0.0f, 0.0f };
	glm::vec2 rotation{ 0.0f, 0.0f };
	glm::vec2 scale{ 0.0f, 0.0f };
};

void TransformComponent::TranslatePosition(sfloat amountToTranslateX, sfloat amountToTranslateY)
{
	position.x += amountToTranslateX;
	position.y += amountToTranslateY;
}

glm::vec2 TransformComponent::GetCurrentPosition()
{
	return position;
}

inline void TransformComponent::SetPosition(sfloat locationX, sfloat locationY)
{
	position.x = locationX;
	position.y = locationY;
}
