#include "Fighter.h"
#include "Components/Transform.h"
#include "PhysicsManager.h"

namespace Blz
{
	namespace Physics
	{
		void Manager::Move(Fighter* p_Fighter, sfloat movementInX, sfloat movementInY)
		{
			p_Fighter->transform.TranslateBy(movementInX, movementInY);
		}
	}
}