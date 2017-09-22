#pragma once
#include <GLM/vec2.hpp>

namespace Comp
{
	class Position
	{
	public:
		void MultiplyBy(int16 const amountToMultipyX, int16 const amountToMultiplyY);
		void Add(sfloat amountToAddX, sfloat amountToAddY);
		void ClampMaxPositionTo(sfloat const maxPositionX, sfloat const maxPositionY);
		void ClampMinPositionTo(sfloat const minPositionX, sfloat const minPositionY);
		glm::vec2 GetCurrentPosition() const;

	private:
		glm::vec2 currentPosition{ 0.0f, 0.0f };
	};
}