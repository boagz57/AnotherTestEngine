#pragma once
#include "../../Components/Transform.h"
#include "../../Components/Velocity.h"

namespace Blz
{
	namespace Physics
	{
		namespace CompSystem
		{
			Comp::Transform MoveFighter(Comp::Transform fighterTransform, Comp::Velocity fighterVelocity);
			//TODO: Will most likely want to remove small utility functions like this eventually by ironing out component/system architecture 
			Comp::Velocity ZeroOutVelocity(Comp::Velocity fighterVelocity);
		}
	}
}