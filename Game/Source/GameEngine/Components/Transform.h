#pragma once
#include <GLM/vec2.hpp>

class TransformComponent
{
public:
	TransformComponent() = default;
	TransformComponent(glm::vec2 position);

	void TranslatePosition(sfloat amountToTranslateX, sfloat amountToTranslateY);
	glm::vec2 GetCurrentPosition();
	void SetPosition(sfloat locationX, sfloat locationY);

private:
	glm::vec2 position{ 0.0f, 0.0f };
	glm::vec2 rotation{ 0.0f, 0.0f };
	glm::vec2 scale{ 0.0f, 0.0f };
};

