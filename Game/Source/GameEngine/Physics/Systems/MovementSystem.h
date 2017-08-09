#pragma once
#include "../../Components/Transform.h"
#include "../../Components/Velocity.h"
#include "../../Fighter.h"

namespace Blz
{
	namespace Physics
	{
		//Returns new translated position
		glm::vec2 MovementSystem(TransformComponent fighterTransform, VelocityComponent fighterVelocity);
	}
}
