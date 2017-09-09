#pragma once
#include "Fighter.h"

namespace Blz
{
	namespace Physics
	{
		class Manager
		{
		public:
			void Move(Fighter* fighter, sfloat movementInX, sfloat movementInY);
		};
	}
}

