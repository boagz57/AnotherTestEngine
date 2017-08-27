#pragma once
#include "Fighter.h"
#include "../../Components/Transform.h"
#include "../../Components/SpriteTileSheet.h"

namespace Blz
{
	namespace GameWorld
	{
		namespace System
		{
			TransformComponent SetFighterStartingPosition(TransformComponent fighterPosition, glm::vec2 fighterStartingPositions);
			SpriteTileSheetComponent SetSpriteWidthAndHeight(SpriteTileSheetComponent fighterSprite, const sfloat spriteWidth, const sfloat spriteHeight);
		}
	}
}
