#pragma once
#include "../../Components/Transform.h"
#include "../../Components/Velocity.h"

namespace Blz
{
	namespace Physics
	{
		namespace System
		{
			TransformComponent MoveFighter(TransformComponent fighterTransform, VelocityComponent fighterVelocity);
			//TODO: Will most likely want to remove small utility functions like this eventually by ironing out component/system architecture 
			VelocityComponent ZeroOutVelocity(VelocityComponent fighterVelocity);
		}
	}
}