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
			Comp::Transform MoveFighter(Comp::Transform fighterTransform, Comp::Velocity fighterVelocity)
			{
				//Move fighter position according to current velocity applied 
				fighterTransform.TranslateBy(fighterVelocity.GetCurrentState().x, fighterVelocity.GetCurrentState().y);

				return fighterTransform;
			}

			Comp::Velocity ZeroOutVelocity(Comp::Velocity fighterVelocity)
			{
				fighterVelocity.ZeroOut();
				return fighterVelocity;
			}
		}
	}
}