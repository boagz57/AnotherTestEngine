#include "Transform.h"

namespace Comp
{
	glm::vec2 const Transform::GetCurrentTranslation() const
	{
		return translation;
	}

	void Transform::TranslateBy(sfloat amountToTranslateX, sfloat amountToTranslateY)
	{
		translation.x += amountToTranslateX;
		translation.y += amountToTranslateY;
	}

	void Transform::ZeroOut()
	{
		translation *= 0;
	}

}