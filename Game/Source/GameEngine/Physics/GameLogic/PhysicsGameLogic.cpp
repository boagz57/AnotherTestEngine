#include "Fighter.h"
#include "PhysicsGameLogic.h"

namespace Blz
{
	namespace Physics
	{
		auto GameLogic::SetCollisionBox(Fighter* const cp_fighter, sfloat width, sfloat height, glm::vec2 position) -> void
		{
			cp_fighter->collisionBox.position = position;
			cp_fighter->collisionBox.width = width;
			cp_fighter->collisionBox.height = height;
		}

		auto GameLogic::Move(Fighter* const p_fighter, const sfloat movementInX, const sfloat movementInY) -> void
		{
			if (movementInX != 0.0f)
				p_fighter->velocity.SetVelocityX(movementInX);
			if (movementInY != 0.0f)
				p_fighter->velocity.SetVelocityY(movementInY);
		}

		auto GameLogic::Jump(Fighter* const p_fighter, const sfloat jumpVelocity) -> void
		{
			if (p_fighter->position.GetCurrentPosition().y == c_groundLevel)
			{
				p_fighter->velocity.SetVelocityY(jumpVelocity);
			}
			else
			{
				return;
			}
		}
	}
}