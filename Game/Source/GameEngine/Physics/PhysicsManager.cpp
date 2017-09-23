#include "Fighter.h"
#include "Components/Transform.h"
#include "PhysicsManager.h"

namespace Blz
{
	namespace Physics
	{
		auto Manager::Move(Fighter* const p_Fighter, const sfloat movementInX, const sfloat movementInY) -> void
		{
			p_Fighter->velocity.SetVelocity(movementInX, movementInY);
		}

		auto Manager::Jump(Fighter * const p_Fighter, const sfloat jumpVelocity) -> void
		{
			if (p_Fighter->position.GetCurrentPosition().y == 5.0f)
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