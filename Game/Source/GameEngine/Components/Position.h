#pragma once
#include <GLM/vec2.hpp>

namespace Comp
{
	class Position
	{
	public:
		void MultiplyPositionBy(int16 const amountToMultipyX, int16 const amountToMultiplyY);
		void SetPosition(sfloat const positionX, sfloat const positionY);
		glm::vec2 const GetCurrentPosition() const;

	private:
		glm::vec2 currentPosition{ 0.0f, 0.0f };
	};
}