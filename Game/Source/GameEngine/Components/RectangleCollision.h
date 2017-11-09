#pragma once
#include <GLM\vec2.hpp>

namespace Comp
{
	struct RectangleCollision
	{
		uint16 width{ 0 };
		uint16 height{ 0 };
		glm::vec2 position{ 0 };
		glm::vec2 bottomLeftCoords{ 0 };
		glm::vec2 topRightCoords{ 0 };
	};
}