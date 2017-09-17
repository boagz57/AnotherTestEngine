#pragma once
#include "Fighter.h"

namespace Blz
{
	namespace Physics
	{
		class Manager
		{
		public:
			auto Move(Fighter* const p_Fighter, const sfloat movementInX, const sfloat movementInY) -> void;
		};
	}
}

