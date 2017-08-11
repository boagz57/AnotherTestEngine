#pragma once
#include "../../Components/Transform.h"
#include "../../Components/Velocity.h"
#include "../../Fighter.h"

namespace Blz
{
	namespace Physics
	{
		//Returns new translated position
		TransformComponent MovementSystem(TransformComponent fighterTransform, VelocityComponent fighterVelocity);
	}
}
