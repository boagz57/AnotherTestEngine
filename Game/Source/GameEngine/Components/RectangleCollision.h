#pragma once
#include <GLM\vec2.hpp>

namespace Comp
{
	struct RectangleCollision
	{
		sfloat width{};
		sfloat height{};
		glm::vec2 position{};
	};
}