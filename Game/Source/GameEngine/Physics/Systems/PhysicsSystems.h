#pragma once
#include "../../Components/Transform.h"
#include "../../Components/Velocity.h"
#include "../../Components/Position.h"

namespace Blz
{
	namespace Physics
	{
		namespace CompSystem
		{
			Comp::Position MoveFighter(Comp::Transform fighterTransform, Comp::Position fighterPosition);
			//TODO: Will most likely want to remove small utility functions like this eventually by ironing out component/system architecture 
			Comp::Velocity ZeroOutVelocity(Comp::Velocity fighterVelocity);
		}
	}
}