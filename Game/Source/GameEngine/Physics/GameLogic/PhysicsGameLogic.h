#pragma once

class Fighter;

namespace Blz::Physics
{
	class GameLogic
	{
	public:
		static auto SetCollisionBox(Fighter* const fighter, sfloat width, sfloat height, glm::vec2 position) -> void;
		static auto Move(Fighter* const fighter, const sfloat movementInX, const sfloat movementInY) -> void;
		static auto Jump(Fighter* const fighter, const sfloat jumpVelocity) -> void;
	};
}

using BlzPhysics = Blz::Physics::GameLogic;