#pragma once
#include <GLM/vec2.hpp>

class TransformComponent
{
public:
	TransformComponent() = default;

	glm::vec2 GetCurrentPosition() const;

	void TranslatePosition(sfloat amountToTranslateX, sfloat amountToTranslateY);
	void MultiplyPosition(int16 const amountToMultipyX, int16 const amountToMultiplyY);
	void SetPosition(sfloat locationX, sfloat locationY);

private:
	glm::vec2 position{ 0.0f, 0.0f };
	glm::vec2 rotation{ 0.0f, 0.0f };
	glm::vec2 scale{ 0.0f, 0.0f };
};

