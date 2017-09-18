#include "Position.h"

namespace Comp
{
	void Position::MultiplyBy(int16 const c_MultiplyX, int16 const c_MultiplyY)
	{
		this->currentPosition.x *= c_MultiplyX;
		this->currentPosition.y *= c_MultiplyY;
	}

	void Position::Add(sfloat amountToAddX, sfloat amountToAddY)
	{
		this->currentPosition.x += amountToAddX;
		this->currentPosition.y += amountToAddY;
	}

	void Position::ClampMaxPositionTo(sfloat const maxPositionX)
	{
		if (currentPosition.x > maxPositionX)
			currentPosition.x = maxPositionX;
	}

	void Position::ClampMinPositionTo(sfloat const minPositionX)
	{
		if (currentPosition.x < minPositionX)
			currentPosition.x = minPositionX;
	}

	glm::vec2 const Position::GetCurrentPosition() const
	{
		return currentPosition;
	}
}