#pragma once
#include <GLM\vec2.hpp>

namespace Comp
{
	struct RectangleCollision
	{
		sfloat width{ 0 };
		sfloat height{ 0 };
		glm::vec2 position{ 0 };
	};
}