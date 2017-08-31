#pragma once
#include <GLM/vec2.hpp>

class TransformComponent
{
public:
	TransformComponent() = default;

	glm::vec2 const GetCurrentTranslation() const;

	void Translate(sfloat amountToTranslateX, sfloat amountToTranslateY);

private:
	glm::vec2 translation{ 0.0f, 0.0f };
	glm::vec2 rotation{ 0.0f, 0.0f };
	glm::vec2 scale{ 0.0f, 0.0f };
};

