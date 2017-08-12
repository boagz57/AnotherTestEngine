#pragma once
#include "../../Components/Transform.h"
#include "../../Components/Sprite.h"

namespace Blz
{
	namespace GameWorld
	{
		namespace System
		{
			TransformComponent SetFighterStartingPosition(TransformComponent fighterPosition, glm::vec2 fighterStartingPositions);
		}
	}
}
