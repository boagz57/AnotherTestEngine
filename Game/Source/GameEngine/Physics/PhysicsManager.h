#pragma once
#include "Fighter.h"

namespace Blz
{
	namespace Physics
	{
		class Manager
		{
		public:
			auto Move(Fighter* const fighter, const sfloat movementInX, const sfloat movementInY) -> void;
			auto Jump(Fighter* const fighter, const sfloat jumpVelocity) -> void;
		};
	}
}

