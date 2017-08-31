#include "../../Fighter.h"
#include "../../Components/Transform.h"
#include "../../Components/Velocity.h"
#include "PhysicsSystems.h"

namespace Blz
{
	namespace Physics
	{
		namespace System
		{
			TransformComponent MoveFighter(TransformComponent fighterTransform, VelocityComponent fighterVelocity)
			{
				//Move fighter position according to current velocity applied 
				fighterTransform.Translate(fighterVelocity.GetCurrentState().x, fighterVelocity.GetCurrentState().y);

				return fighterTransform;
			}

			VelocityComponent ZeroOutVelocity(VelocityComponent fighterVelocity)
			{
				fighterVelocity.ZeroOut();
				return fighterVelocity;
			}
		}
	}
}