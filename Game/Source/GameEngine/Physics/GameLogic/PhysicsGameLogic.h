#pragma once
#include "Fighter.h"

namespace Blz::Physics
{
	class GameLogic
	{
	public:
		static auto Move(Fighter* const fighter, const sfloat movementInX, const sfloat movementInY) -> void;
		static auto Jump(Fighter* const fighter, const sfloat jumpVelocity) -> void;
	};
}

using BlzPhysics = Blz::Physics::GameLogic;