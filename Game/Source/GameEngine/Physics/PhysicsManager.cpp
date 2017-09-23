#include "Fighter.h"
#include "Components/Transform.h"
#include "PhysicsManager.h"

namespace Blz
{
	namespace Physics
	{
		auto Manager::Move(Fighter* const p_Fighter, const sfloat movementInX, const sfloat movementInY) -> void
		{
			if (movementInX != 0.0f)
				p_Fighter->velocity.SetVelocityX(movementInX);
			if (movementInY != 0.0f)
				p_Fighter->velocity.SetVelocityY(movementInY);
		}

		auto Manager::Jump(Fighter * const p_Fighter, const sfloat jumpVelocity) -> void
		{
			sfloat groundLevel = 5.0f;

			if (p_Fighter->position.GetCurrentPosition().y == groundLevel)
			{
				p_Fighter->velocity.SetVelocityY(jumpVelocity);
			}
			else
			{
				return;
			}
		}
	}
}