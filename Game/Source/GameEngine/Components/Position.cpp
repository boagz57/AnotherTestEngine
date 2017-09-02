#include "Position.h"

namespace Comp
{
	void Position::MultiplyPositionBy(int16 const c_MultiplyX, int16 const c_MultiplyY)
	{
		this->currentPosition.x *= c_MultiplyX;
		this->currentPosition.y *= c_MultiplyY;
	}

	void Position::SetPosition(sfloat const positionX, sfloat const positionY)
	{
		currentPosition.x = positionX;
		currentPosition.y = positionY;
	}

	glm::vec2 const Position::GetCurrentPosition() const
	{
		return currentPosition;
	}
}