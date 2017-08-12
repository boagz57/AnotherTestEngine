#pragma once
#include "../../Components/Transform.h"
#include "../../Components/Velocity.h"
#include "../../Fighter.h"

namespace Blz
{
	namespace Physics
	{
		namespace System
		{
			//Returns new translated position
			TransformComponent MovementSystem(TransformComponent fighterTransform, VelocityComponent fighterVelocity);
		}
	}
}
