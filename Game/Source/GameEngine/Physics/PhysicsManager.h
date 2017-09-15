#pragma once
#include "Fighter.h"

namespace Blz
{
	namespace Physics
	{
		class Manager
		{
		public:
			auto Move(Fighter* fighter, sfloat movementInX, sfloat movementInY) -> void;
		};
	}
}

