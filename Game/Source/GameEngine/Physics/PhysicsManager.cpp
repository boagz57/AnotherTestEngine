#include "Fighter.h"
#include "Components/Transform.h"
#include "PhysicsManager.h"

namespace Blz
{
	namespace Physics
	{
		void Manager::Move(Fighter* p_Fighter, sfloat movementInX, sfloat movementInY)
		{
			Comp::Transform fighterTransform = p_Fighter->GetComponent<Comp::Transform>();

			fighterTransform.TranslateBy(movementInX, movementInY);

			p_Fighter->Insert(fighterTransform);
		}
	}
}