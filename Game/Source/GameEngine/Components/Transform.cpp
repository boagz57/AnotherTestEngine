#include "Transform.h"

namespace Comp
{
	glm::vec2 const Transform::GetCurrentTranslation() const
	{
		return translation;
	}

	void Transform::Translate(sfloat amountToTranslateX, sfloat amountToTranslateY)
	{
		translation.x += amountToTranslateX;
		translation.y += amountToTranslateY;
	}
}