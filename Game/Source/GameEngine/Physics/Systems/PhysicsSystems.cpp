#include "../../Fighter.h"
#include "../../Components/Transform.h"
#include "../../Components/Velocity.h"
#include "PhysicsSystems.h"

namespace Blz
{
	namespace Physics
	{
		namespace CompSystem
		{
			Comp::Position MoveFighter(Comp::Transform fighterTransform, Comp::Position fighterPosition)
			{
				fighterPosition.AddBy(fighterTransform.GetCurrentTranslation().x, fighterTransform.GetCurrentTranslation().y);

				return fighterPosition;
			}

			Comp::Velocity ZeroOutVelocity(Comp::Velocity fighterVelocity)
			{
				fighterVelocity.ZeroOut();
				return fighterVelocity;
			}
		}
	}
}