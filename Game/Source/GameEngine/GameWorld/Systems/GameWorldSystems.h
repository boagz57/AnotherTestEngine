#pragma once
#include "Fighter.h"
#include "../../Components/Transform.h"
#include "../../Components/Sprite.h"

namespace Blz
{
	namespace GameWorld
	{
		namespace System
		{
			TransformComponent SetFighterStartingPosition(TransformComponent fighterPosition, glm::vec2 fighterStartingPositions);
			SpriteComponent SetSpriteWidthAndHeight(SpriteComponent fighterSprite, const sfloat spriteWidth, const sfloat spriteHeight);
		}
	}
}
