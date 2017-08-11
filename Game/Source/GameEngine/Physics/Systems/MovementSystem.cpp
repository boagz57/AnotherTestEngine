#include "../../Fighter.h"
#include "../../Components/Transform.h"
#include "../../Components/Velocity.h"
#include "MovementSystem.h"

namespace Blz
{
	namespace Physics
	{
		TransformComponent MovementSystem(TransformComponent fighterTransform, VelocityComponent fighterVelocity)
		{
			//Move fighter position according to current velocity applied 
			fighterTransform.TranslatePosition(fighterVelocity.GetCurrentState().x, fighterVelocity.GetCurrentState().y);

			return fighterTransform.GetCurrentPosition();
		}
	}
}