#include "Fighter.h"
#include "Components/Transform.h"
#include "PhysicsManager.h"

namespace Blz
{
	namespace Physics
	{
		auto Manager::Move(Fighter* p_Fighter, sfloat movementInX, sfloat movementInY) -> void
		{
			p_Fighter->transform.TranslateBy(movementInX, movementInY);
			p_Fighter->velocity.Add(movementInX, movementInY);
		}
	}
}