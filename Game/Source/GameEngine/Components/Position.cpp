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

	void Position::ClampMaxPositionTo(sfloat const maxPositionX, sfloat const maxPositionY)
	{
		if (currentPosition.x > maxPositionX)
			currentPosition.x = maxPositionX;
		if (currentPosition.y > maxPositionY)
			currentPosition.y = maxPositionY;
	}

	void Position::ClampMinPositionTo(sfloat const minPositionX, sfloat const minPositionY)
	{
		if (currentPosition.x < minPositionX)
			currentPosition.x = minPositionX;
		if (currentPosition.y < minPositionY)
			currentPosition.y = minPositionY;
	}

	glm::vec2 Position::GetCurrentPosition() const
	{
		return currentPosition;
	}
}